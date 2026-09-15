#include "hasher.h"
#include "walker.h"
#include "output.h"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

static void print_usage() {
    std::cout <<
        "Usage: hashcheck [options] <path>\n"
        "\n"
        "Options:\n"
        "  --algo <name>     sha256 | sha512 | md5   (default: sha256)\n"
        "  --recursive, -r   walk directories recursively\n"
        "  --format <fmt>    plain | csv | json      (default: plain)\n"
        "  --output <file>   write to file instead of stdout\n"
        "  --help, -h        show this message\n"
        "\n"
        "Examples:\n"
        "  hashcheck --algo sha256 file.bin\n"
        "  hashcheck -r --format json ./data\n";
}

int main(int argc, char** argv) {
    hashcheck::Algorithm algo = hashcheck::Algorithm::SHA256;
    hashcheck::Format format = hashcheck::Format::Plain;
    bool recursive = false;
    std::string output_path;
    std::vector<std::string> targets;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            print_usage();
            return 0;
        } else if (arg == "--algo" && i + 1 < argc) {
            if (!hashcheck::parse_algorithm(argv[++i], algo)) {
                std::cerr << "error: unknown algorithm: " << argv[i] << "\n";
                return 3;
            }
        } else if (arg == "--format" && i + 1 < argc) {
            if (!hashcheck::parse_format(argv[++i], format)) {
                std::cerr << "error: unknown format: " << argv[i] << "\n";
                return 3;
            }
        } else if (arg == "--output" && i + 1 < argc) {
            output_path = argv[++i];
        } else if (arg == "--recursive" || arg == "-r") {
            recursive = true;
        } else if (arg.size() > 0 && arg[0] == '-') {
            std::cerr << "error: unknown option: " << arg << "\n";
            return 3;
        } else {
            targets.push_back(arg);
        }
    }

    if (targets.empty()) {
        print_usage();
        return 3;
    }

    std::vector<hashcheck::Entry> entries;
    int read_errors = 0;

    for (const auto& target : targets) {
        std::error_code ec;
        if (!fs::exists(target, ec)) {
            std::cerr << "warning: not found: " << target << "\n";
            ++read_errors;
            continue;
        }

        auto process_one = [&](const std::string& path) {
            std::string digest = hashcheck::hash_file(algo, path);
            if (digest.empty()) {
                std::cerr << "warning: cannot read: " << path << "\n";
                ++read_errors;
                return;
            }
            std::error_code ec2;
            auto sz = fs::file_size(path, ec2);
            hashcheck::Entry e;
            e.path   = path;
            e.algo   = hashcheck::algorithm_name(algo);
            e.digest = digest;
            e.size   = ec2 ? 0 : (uint64_t)sz;
            entries.push_back(e);
        };

        if (fs::is_directory(target, ec)) {
            if (!recursive) {
                std::cerr << "warning: " << target
                          << " is a directory (use --recursive)\n";
                continue;
            }
            hashcheck::walk_directory(target, process_one);
        } else {
            process_one(target);
        }
    }

    std::ostream* out = &std::cout;
    std::ofstream file_out;
    if (!output_path.empty()) {
        file_out.open(output_path);
        if (!file_out) {
            std::cerr << "error: cannot open output file: " << output_path << "\n";
            return 1;
        }
        out = &file_out;
    }

    hashcheck::write_output(format, entries, *out);

    return read_errors > 0 ? 1 : 0;
}
#pragma once

#include <string>
#include <vector>

namespace hashcheck {

enum class Format {
    Plain,
    CSV,
    JSON,
};

bool parse_format(const std::string& name, Format& out);

struct Entry {
    std::string path;
    std::string algo;
    std::string digest;
    uint64_t    size;
};

// 把 entries 按 format 输出到 out 流
void write_output(Format format,
                  const std::vector<Entry>& entries,
                  std::ostream& out);

}  // namespace hashcheck
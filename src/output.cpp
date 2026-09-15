#include "output.h"

#include <ostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

namespace hashcheck {

bool parse_format(const std::string& name, Format& out) {
    std::string lower = name;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "plain") { out = Format::Plain; return true; }
    if (lower == "csv")   { out = Format::CSV;   return true; }
    if (lower == "json")  { out = Format::JSON;  return true; }
    return false;
}

static std::string csv_escape(const std::string& s) {
    if (s.find_first_of(",\"\n") == std::string::npos) return s;
    std::string out = "\"";
    for (char c : s) {
        if (c == '"') out += "\"\"";
        else out += c;
    }
    out += '"';
    return out;
}

static std::string json_escape(const std::string& s) {
    std::string out;
    for (char c : s) {
        switch (c) {
            case '"':  out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            default:
                if ((unsigned char)c < 0x20) {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "\\u%04x", c);
                    out += buf;
                } else {
                    out += c;
                }
        }
    }
    return out;
}

void write_output(Format format,
                  const std::vector<Entry>& entries,
                  std::ostream& out) {
    switch (format) {
        case Format::Plain: {
            for (const auto& e : entries) {
                out << e.digest << "  " << e.path << "\n";
            }
            break;
        }
        case Format::CSV: {
            out << "path,algo,digest,size\n";
            for (const auto& e : entries) {
                out << csv_escape(e.path) << ","
                    << e.algo << ","
                    << e.digest << ","
                    << e.size << "\n";
            }
            break;
        }
        case Format::JSON: {
            std::time_t now = std::time(nullptr);
            std::tm tm_buf{};
#if defined(_WIN32)
            gmtime_s(&tm_buf, &now);
#else
            gmtime_r(&now, &tm_buf);
#endif
            char ts[32];
            std::strftime(ts, sizeof(ts), "%Y-%m-%dT%H:%M:%SZ", &tm_buf);

            out << "{\n";
            out << "  \"generated_at\": \"" << ts << "\",\n";
            out << "  \"entries\": [\n";
            for (size_t i = 0; i < entries.size(); ++i) {
                const auto& e = entries[i];
                out << "    {"
                    << "\"path\": \"" << json_escape(e.path) << "\", "
                    << "\"algo\": \"" << e.algo << "\", "
                    << "\"digest\": \"" << e.digest << "\", "
                    << "\"size\": " << e.size
                    << "}";
                if (i + 1 < entries.size()) out << ",";
                out << "\n";
            }
            out << "  ]\n";
            out << "}\n";
            break;
        }
    }
}

}  // namespace hashcheck
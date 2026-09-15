#include "walker.h"

#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;

namespace hashcheck {

size_t walk_directory(const std::string& root,
                      const std::function<void(const std::string&)>& callback) {
    size_t count = 0;

    std::error_code ec;
    if (!fs::exists(root, ec)) return 0;

    if (fs::is_regular_file(root, ec)) {
        callback(root);
        return 1;
    }

    for (auto it = fs::recursive_directory_iterator(
             root, fs::directory_options::skip_permission_denied, ec);
         it != fs::recursive_directory_iterator(); it.increment(ec)) {
        if (ec) break;
        if (!it->is_regular_file(ec)) continue;
        callback(it->path().string());
        ++count;
    }

    return count;
}

}  // namespace hashcheck
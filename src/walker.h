#pragma once

#include <string>
#include <vector>
#include <functional>

namespace hashcheck {

// 遍历目录（递归），对每个文件调用 callback
// 返回成功遍历的文件数
size_t walk_directory(const std::string& root,
                      const std::function<void(const std::string&)>& callback);

}  // namespace hashcheck
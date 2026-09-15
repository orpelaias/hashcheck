#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace hashcheck {

enum class Algorithm {
    SHA256,
    SHA512,
    MD5,
};

// 把算法名（"sha256"）转成枚举，失败返回 false
bool parse_algorithm(const std::string& name, Algorithm& out);

// 把算法转成显示名（"sha256"）
const char* algorithm_name(Algorithm algo);

// 对内存里的数据算 hash，返回十六进制字符串
std::string hash_bytes(Algorithm algo, const void* data, size_t size);

// 对文件算 hash，失败返回空字符串
std::string hash_file(Algorithm algo, const std::string& path);

}  // namespace hashcheck
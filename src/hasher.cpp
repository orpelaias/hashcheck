#include "hasher.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <algorithm>

#include <openssl/evp.h>

namespace hashcheck {

bool parse_algorithm(const std::string& name, Algorithm& out) {
    std::string lower = name;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "sha256") { out = Algorithm::SHA256; return true; }
    if (lower == "sha512") { out = Algorithm::SHA512; return true; }
    if (lower == "md5")    { out = Algorithm::MD5;    return true; }
    return false;
}

const char* algorithm_name(Algorithm algo) {
    switch (algo) {
        case Algorithm::SHA256: return "sha256";
        case Algorithm::SHA512: return "sha512";
        case Algorithm::MD5:    return "md5";
    }
    return "unknown";
}

static const EVP_MD* get_md(Algorithm algo) {
    switch (algo) {
        case Algorithm::SHA256: return EVP_sha256();
        case Algorithm::SHA512: return EVP_sha512();
        case Algorithm::MD5:    return EVP_md5();
    }
    return nullptr;
}

std::string hash_bytes(Algorithm algo, const void* data, size_t size) {
    const EVP_MD* md = get_md(algo);
    if (!md) return "";

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) return "";

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len = 0;

    bool ok = EVP_DigestInit_ex(ctx, md, nullptr) == 1
           && EVP_DigestUpdate(ctx, data, size) == 1
           && EVP_DigestFinal_ex(ctx, digest, &digest_len) == 1;

    EVP_MD_CTX_free(ctx);
    if (!ok) return "";

    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < digest_len; ++i) {
        oss << std::setw(2) << (int)digest[i];
    }
    return oss.str();
}

std::string hash_file(Algorithm algo, const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f.is_open()) return "";

    const EVP_MD* md = get_md(algo);
    if (!md) return "";

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) return "";

    if (EVP_DigestInit_ex(ctx, md, nullptr) != 1) {
        EVP_MD_CTX_free(ctx);
        return "";
    }

    char buf[65536];
    while (f.good()) {
        f.read(buf, sizeof(buf));
        std::streamsize n = f.gcount();
        if (n > 0) {
            if (EVP_DigestUpdate(ctx, buf, (size_t)n) != 1) {
                EVP_MD_CTX_free(ctx);
                return "";
            }
        }
    }

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len = 0;
    if (EVP_DigestFinal_ex(ctx, digest, &digest_len) != 1) {
        EVP_MD_CTX_free(ctx);
        return "";
    }
    EVP_MD_CTX_free(ctx);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < digest_len; ++i) {
        oss << std::setw(2) << (int)digest[i];
    }
    return oss.str();
}

}  // namespace hashcheck
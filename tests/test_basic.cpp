// Basic smoke test for hashcheck.
// Not wired into CTest by default — see docs/BUILD.md for manual invocation.

#include "../src/hasher.h"

#include <cassert>
#include <iostream>
#include <cstring>

int main() {
    using namespace hashcheck;

    // Known-answer test: SHA-256 of "abc"
    // Reference: FIPS 180-4 test vector
    const char* input = "abc";
    std::string expected =
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";

    std::string actual = hash_bytes(Algorithm::SHA256, input, std::strlen(input));
    assert(actual == expected);

    // Empty input SHA-256
    std::string empty_expected =
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    std::string empty_actual = hash_bytes(Algorithm::SHA256, "", 0);
    assert(empty_actual == empty_expected);

    // Algorithm parsing
    Algorithm a;
    assert(parse_algorithm("sha256", a) && a == Algorithm::SHA256);
    assert(parse_algorithm("MD5", a)    && a == Algorithm::MD5);
    assert(!parse_algorithm("nope", a));

    std::cout << "All tests passed.\n";
    return 0;
}
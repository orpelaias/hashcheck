markdown
# Building hashcheck from source

## Prerequisites

- C++17 compiler (MSVC 2019+, GCC 9+, Clang 10+)
- CMake 3.15 or newer
- OpenSSL development headers

## Windows

1. Install OpenSSL via vcpkg:
vcpkg install openssl:x64-windows

text

2. Configure and build:
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release

text

3. The binary is at `build/Release/hashcheck.exe`.

## macOS
brew install openssl cmake
cmake -B build -DCMAKE_BUILD_TYPE=Release -DOPENSSL_ROOT_DIR=$(brew --prefix openssl)
cmake --build build

text

## Linux
sudo apt install libssl-dev cmake g++
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

text

## Running tests
ctest --test-dir build

text

## Packaging a release
cmake --build build --config Release
cmake --install build --prefix dist

text

The resulting binary is self-contained and requires no runtime dependencies
beyond the operating system's standard C++ runtime.
cmake_minimum_required(VERSION 3.15)
project(hashcheck VERSION 1.4.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(OpenSSL REQUIRED)

add_executable(hashcheck
    src/main.cpp
    src/hasher.cpp
    src/walker.cpp
    src/output.cpp
)

target_include_directories(hashcheck PRIVATE src)
target_link_libraries(hashcheck PRIVATE OpenSSL::Crypto)

if(MSVC)
    target_compile_options(hashcheck PRIVATE /W4 /utf-8)
else()
    target_compile_options(hashcheck PRIVATE -Wall -Wextra)
endif()

# ---- Tests ----
enable_testing()

add_executable(test_basic
    tests/test_basic.cpp
    src/hasher.cpp
)

target_include_directories(test_basic PRIVATE src)
target_link_libraries(test_basic PRIVATE OpenSSL::Crypto)

add_test(NAME basic COMMAND test_basic)

# ---- Install ----
install(TARGETS hashcheck RUNTIME DESTINATION bin)
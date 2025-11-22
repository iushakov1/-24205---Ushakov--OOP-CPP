cmake_minimum_required(VERSION 3.15)
project(task-1)

set(CMAKE_CXX_STANDARD 20)

add_executable(task-1 src/bitarray.cpp
        src/main.cpp)

enable_testing()

find_package(GTest REQUIRED)

add_executable(batests
        tests/test_bitarray.cpp
        src/bitarray.cpp)
include_directories(src)
target_link_libraries(batests GTest::gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(batests)
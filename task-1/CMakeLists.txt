cmake_minimum_required(VERSION 3.29)
project(task_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_1 src/main.cpp
        src/bitarray.cpp
        src/bitarray.h)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} src)

add_executable(runTests
        src/bitarray.cpp
        tests/test_bitarray.cpp
)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)
add_test(NAME runTests COMMAND runTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
cmake_minimum_required(VERSION 3.29)
project(task_0b)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_0b
        src/main.cpp
        src/wordcounter.h
        src/wordcounter.cpp
        src/filereader.cpp
        src/filereader.h
        src/csvwriter.cpp
        src/csvwriter.h
)
target_include_directories(task_0b PRIVATE src)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} src)

add_executable(runTests
        tests/test_wordcounter.cpp
        src/wordcounter.cpp
        src/filereader.cpp
        src/csvwriter.cpp
        tests/test_filereader.cpp
        tests/test_csvwriter.cpp
)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)
add_test(NAME runTests COMMAND runTests)
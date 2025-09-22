cmake_minimum_required(VERSION 3.29)
project(task_0b)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_0b
        src/main.cpp
        src/ResultWriter.cpp
        src/WordCounter.cpp
        src/TextReader.cpp)
target_include_directories(task_0b PRIVATE src)

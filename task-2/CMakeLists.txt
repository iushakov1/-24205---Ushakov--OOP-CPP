cmake_minimum_required(VERSION 3.29)
project(task_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task_2
        src/main.cpp
        src/universe.cpp
        src/stepper.cpp
        src/rule.cpp
        src/filereader.cpp
        src/filewritter.cpp
        src/render.cpp
        src/simulator.cpp
        src/parser.cpp
        src/presetregistry.cpp
        src/presetio.cpp
)

find_package(GTest REQUIRED)

add_executable(UnitTests
        tests/parsertest.cpp
        tests/presetiotest.cpp
        tests/presetregistrytest.cpp
        tests/rendertest.cpp
        tests/simulator.cpp
        tests/ruletests.cpp
        tests/stepper.cpp
        tests/universetests.cpp
)

target_link_libraries(UnitTests PRIVATE
        GTest::gtest GTest::gtest_main)

target_include_directories(UnitTests PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_sources(UnitTests PRIVATE
        src/simulator.cpp
        src/universe.cpp
        src/stepper.cpp
        src/rule.cpp
        src/filereader.cpp
        src/filewritter.cpp
        src/parser.cpp
        src/presetregistry.cpp
        src/presetio.cpp
        src/render.cpp
)

include(GoogleTest)

gtest_discover_tests(UnitTests)

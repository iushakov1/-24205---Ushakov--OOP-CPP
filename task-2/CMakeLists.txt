cmake_minimum_required(VERSION 3.29)
project(task_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task_2
        src/main.cpp
        src/universe.cpp
        src/rule.cpp
        src/filereader.cpp
        src/filewritter.cpp
        src/render.cpp
        src/presetregistry.cpp
        src/preset.cpp
        src/preset.h
        src/command.cpp
        src/command.h
        src/mode.cpp
        src/mode.h
        src/commandparser.cpp
        src/commandparser.h
        src/modeparser.cpp
        src/modeparser.h
)

find_package(GTest REQUIRED)

add_executable(UnitTests
        tests/ruletests.cpp
        tests/universetests.cpp
        tests/commandtests.cpp
        tests/commandparsertests.cpp
        tests/modeparser.cpp
        tests/presettests.cpp
        tests/presetregistry.cpp
        tests/filereadertests.cpp
        tests/filewrittertests.cpp
        tests/modetests.cpp

)

target_link_libraries(UnitTests PRIVATE
        GTest::gtest GTest::gtest_main)

target_include_directories(UnitTests PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_sources(UnitTests PRIVATE
        src/rule.cpp
        src/universe.cpp
        src/command.cpp
        src/commandparser.cpp
        src/filereader.cpp
        src/filewritter.cpp
        src/mode.cpp
        src/modeparser.cpp
        src/preset.cpp
        src/presetregistry.cpp
        src/render.cpp
)

include(GoogleTest)

gtest_discover_tests(UnitTests)

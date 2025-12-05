//
// Created by ioanushakov on 05.12.2025.
//

#include "filewritter.h"

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

static fs::path makePath(const std::string& name) {
    fs::path dir = "filewriter_tests";
    fs::create_directories(dir);
    return dir / name;
}

TEST(FileWriterTest, CreatesAndWritesLines) {
    fs::path path = makePath("create_and_write.txt");

    FileWriter writer(path.string());
    writer.write("line1");
    writer.write("line2");
    writer.write("line3");
    writer.close();

    std::ifstream in(path);
    ASSERT_TRUE(in.is_open());

    std::string line;
    std::getline(in, line);
    EXPECT_EQ(line, "line1");
    std::getline(in, line);
    EXPECT_EQ(line, "line2");
    std::getline(in, line);
    EXPECT_EQ(line, "line3");
    EXPECT_FALSE(std::getline(in, line));

    fs::remove_all(path.parent_path());
}

TEST(FileWriterTest, OpenCloseReopenAppend) {
    fs::path path = makePath("reopen.txt");

    FileWriter writer(path.string());
    writer.write("first");
    writer.close();
    writer.open();
    writer.write("second");
    writer.close();

    std::ifstream in(path);
    ASSERT_TRUE(in.is_open());
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }

    EXPECT_FALSE(lines.empty());
}

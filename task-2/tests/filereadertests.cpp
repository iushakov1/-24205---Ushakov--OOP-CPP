//
// Created by ioanushakov on 05.12.2025.
//

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "filereader.h"

namespace fs = std::filesystem;

static fs::path createTestFile(const std::string& name) {
    fs::path dir = "filereader_tests";
    fs::create_directories(dir);
    fs::path file = dir / name;

    std::ofstream out(file);
    out << "line1\n";
    out << "line2\n";
    out << "line3\n";
    return file;
}

TEST(FileReaderTest, ReadsLines) {
    fs::path file = createTestFile("sequential.txt");

    FileReader reader(file.string());

    ASSERT_TRUE(reader.hasNext());
    EXPECT_EQ(reader.next(), "line1");
    ASSERT_TRUE(reader.hasNext());
    EXPECT_EQ(reader.next(), "line2");
    ASSERT_TRUE(reader.hasNext());
    EXPECT_EQ(reader.next(), "line3");

    fs::remove_all(file.parent_path());
}

TEST(FileReaderTest, ResetMovesBackToBeginning) {
    fs::path file = createTestFile("reset.txt");
    FileReader reader(file.string());

    EXPECT_EQ(reader.next(), "line1");
    EXPECT_EQ(reader.next(), "line2");

    reader.reset();

    EXPECT_EQ(reader.next(), "line1");
    EXPECT_EQ(reader.next(), "line2");
    EXPECT_EQ(reader.next(), "line3");

    fs::remove_all(file.parent_path());
}

TEST(FileReaderTest, CloseAndOpenReopenFile) {
    fs::path file = createTestFile("reopen.txt");
    FileReader reader(file.string());

    EXPECT_EQ(reader.next(), "line1");

    reader.close();
    reader.open();

    EXPECT_EQ(reader.next(), "line1");

    fs::remove_all(file.parent_path());
}

TEST(FileReaderTest, HasNextOnEmptyFile) {
    fs::path dir = fs::temp_directory_path() / "filereader_empty";
    fs::create_directories(dir);
    fs::path file = dir / "empty.txt";
    {
        std::ofstream out(file);
    }

    FileReader reader(file.string());

    std::string line = reader.next();
    EXPECT_EQ(line, "");
    EXPECT_FALSE(reader.hasNext());

    fs::remove_all(dir);
}
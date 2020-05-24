#include <cstdlib>
#include <string>
#include <gtest/gtest.h>
#include "file_reader.hpp"

std::string basedir;

TEST(FileReaderTest, readLine)
{
    file_reader reader(basedir + "resources/FileReaderTest__readLine.gcode");

    std::string result = reader.get_line();

    EXPECT_EQ("G0 X10 Y10", result);
}

TEST(FileReaderTest, readLine_WhenEmptyLine)
{
    file_reader reader(basedir + "resources/FileReaderTest__readLine_WhenEmptyLine.gcode");

    std::string result0 = reader.get_line();
    std::string result1 = reader.get_line();
    std::string result2 = reader.get_line();

    EXPECT_EQ("G0 X10 Y10", result0);
    EXPECT_EQ("", result1);
    EXPECT_EQ("G1 X40 Y40", result2);
}

TEST(FileReaderTest, readLine_WhenTrailingComment)
{
    file_reader reader(basedir + "resources/FileReaderTest__readLine_WhenTrailingComment.gcode");

    std::string result = reader.get_line();

    EXPECT_EQ("G2 X200 Y200 R100", result);
}

int main(int argc, char * argv[])
{
    std::string command = argv[0];
    int index = command.find_last_of("/");

    ::testing::InitGoogleTest(&argc, argv);
    basedir = command.substr(0, index) + "/";
    return RUN_ALL_TESTS();
}

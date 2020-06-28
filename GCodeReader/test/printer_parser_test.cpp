#include <cstdlib>
#include <vector>
#include <gtest/gtest.h>
#include "parser.hpp"

TEST(PrinterParserTest, parse_whenEmptyList_thenNoInstructions)
{
    // given
    printer_parser test_object({});
    // when
    test_object.parse();
    // then
    EXPECT_EQ(std::vector<printer_instruction>(), test_object.get_instructions());
}

TEST(PrinterParserTest, parse_whenG0_thenSingleG0Instruction)
{
    // given
    vec start;
    gcode_instruction g0(1);
    printer_instruction expected("1", start);

    g0.add_argument('G', 0);
    g0.add_argument('X', 10);
    g0.add_argument('Y', 10);
    expected.add_argument(std::make_pair('G', 0));
    expected.add_argument(std::make_pair('X', 10));
    expected.add_argument(std::make_pair('Y', 10));

    printer_parser test_object(std::vector<gcode_instruction>({g0}), start);

    // when
    test_object.parse();
    // then
    EXPECT_EQ(std::vector<printer_instruction>({expected}), test_object.get_instructions());
}

TEST(PrinterParserTest, parse_whenG1_thenSingleG1Instruction)
{
    // given
    vec start;
    gcode_instruction g1(1);
    printer_instruction expected("1", start);

    g1.add_argument('G', 1);
    g1.add_argument('X', 10);
    g1.add_argument('Y', 10);
    expected.add_argument(std::make_pair('G', 1));
    expected.add_argument(std::make_pair('X', 10));
    expected.add_argument(std::make_pair('Y', 10));

    printer_parser test_object(std::vector<gcode_instruction>({g1}), start);

    // when
    test_object.parse();
    // then
    EXPECT_EQ(std::vector<printer_instruction>({expected}), test_object.get_instructions());
}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

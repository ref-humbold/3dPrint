#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "parser.hpp"

std::vector<printer_instruction> moves(std::vector<vec> points, bool mode)
{
    std::vector<printer_instruction> instructions;
    int g_arg = mode ? 1 : 0;

    for(size_t i = 1; i < points.size(); ++i)
    {
        grid pt(points[i]);
        printer_instruction instr(std::to_string(i), points[i - 1]);

        instr.add_argument(std::make_pair('G', g_arg));
        instr.add_argument(std::make_pair('X', pt.x));
        instr.add_argument(std::make_pair('Y', pt.y));
        instructions.push_back(instr);
    }

    return instructions;
}

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
    std::vector<vec> points = {vec(0, 0), vec(10, 10)};
    gcode_instruction g0(0);
    g0.add_argument('G', 0);
    g0.add_argument('X', 10);
    g0.add_argument('Y', 10);

    printer_instruction expected = moves(points, false).at(0);
    printer_parser test_object(std::vector<gcode_instruction>({g0}), points[0]);
    // when
    test_object.parse();
    // then
    EXPECT_EQ(std::vector<printer_instruction>({expected}), test_object.get_instructions());
}

TEST(PrinterParserTest, parse_whenG1_thenSingleG1Instruction)
{
    // given
    std::vector<vec> points = {vec(0, 0), vec(10, 10)};
    gcode_instruction g1(0);
    g1.add_argument('G', 1);
    g1.add_argument('X', 10);
    g1.add_argument('Y', 10);

    printer_instruction expected = moves(points, true).at(0);
    printer_parser test_object(std::vector<gcode_instruction>({g1}), points[0]);
    // when
    test_object.parse();
    // then
    EXPECT_EQ(std::vector<printer_instruction>({expected}), test_object.get_instructions());
}

TEST(PrinterParserTest, parse_whenG2WithPositiveRadius_thenG1InstructionsAlongArc)
{
    // given
    std::vector<vec> points = {vec(139, 92),  vec(139, 93),  vec(140, 97), vec(140, 100),
                               vec(140, 103), vec(139, 107), vec(139, 108)};
    gcode_instruction g2(0);
    g2.add_argument('G', 2);
    g2.add_argument('X', points.back().x);
    g2.add_argument('Y', points.back().y);
    g2.add_argument('R', 40);

    std::vector<printer_instruction> expected = moves(points, true);
    printer_parser test_object(std::vector<gcode_instruction>({g2}), points[0]);
    // when
    test_object.parse();
    // then
    EXPECT_EQ(expected, test_object.get_instructions());
}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

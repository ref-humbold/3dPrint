#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "parser.hpp"

std::vector<printer_instruction> moves(std::vector<vec> points, std::vector<int> modes)
{
    std::vector<printer_instruction> instructions;
    grid prev_point(points[0]);

    for(size_t i = 1; i < points.size(); ++i)
    {
        grid pt(points[i]);

        if(pt != prev_point)
        {
            printer_instruction instr(std::to_string(i), points[i - 1]);

            instr.add_argument(std::make_pair('G', modes[i]));
            instr.add_argument(std::make_pair('X', pt.x));
            instr.add_argument(std::make_pair('Y', pt.y));
            instructions.push_back(instr);
        }

        prev_point = pt;
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
    EXPECT_EQ(std::vector<printer_instruction>(), test_object.instructions());
}

TEST(PrinterParserTest, parse_whenG0_thenSingleG0Instruction)
{
    // given
    std::vector<vec> points = {vec(0, 0), vec(10, 10)};
    std::vector<int> modes(points.size(), 0);

    gcode_instruction g0(0);
    g0.add_argument('G', 0);
    g0.add_argument('X', 10);
    g0.add_argument('Y', 10);

    std::vector<printer_instruction> expected = moves(points, modes);
    printer_parser test_object(std::vector<gcode_instruction>({g0}), points[0]);
    // when
    test_object.parse();
    // then
    ASSERT_EQ(1, test_object.instructions().size());
    EXPECT_EQ(expected, test_object.instructions());
}

TEST(PrinterParserTest, parse_whenG1_thenSingleG1Instruction)
{
    // given
    std::vector<vec> points = {vec(0, 0), vec(10, 10)};
    std::vector<int> modes(points.size(), 1);

    gcode_instruction g1(0);
    g1.add_argument('G', 1);
    g1.add_argument('X', 10);
    g1.add_argument('Y', 10);

    std::vector<printer_instruction> expected = moves(points, modes);
    printer_parser test_object(std::vector<gcode_instruction>({g1}), points[0]);
    // when
    test_object.parse();
    // then
    ASSERT_EQ(1, test_object.instructions().size());
    EXPECT_EQ(expected, test_object.instructions());
}

TEST(PrinterParserTest, parse_whenG2WithPositiveRadius_thenG1InstructionsAlongArc)
{
    // given
    std::vector<vec> points = {vec(139, 108), vec(139, 107), vec(140, 103), vec(140, 100),
                               vec(140, 97),  vec(139, 93),  vec(139, 92)};
    std::vector<int> modes(points.size(), 1);

    gcode_instruction g2(0);
    g2.add_argument('G', 2);
    g2.add_argument('X', points.back().x);
    g2.add_argument('Y', points.back().y);
    g2.add_argument('R', 40);

    std::vector<printer_instruction> expected = moves(points, modes);
    printer_parser test_object(std::vector<gcode_instruction>({g2}), points[0]);
    // when
    test_object.parse();
    // then
    ASSERT_EQ(6, test_object.instructions().size());
    EXPECT_EQ(expected, test_object.instructions());
}

TEST(PrinterParserTest, parse_whenG3WithPositiveRadius_thenG1InstructionsAlongArc)
{
    // given
    std::vector<vec> points = {vec(139, 92),  vec(139, 93),  vec(140, 97), vec(140, 100),
                               vec(140, 103), vec(139, 107), vec(139, 108)};
    std::vector<int> modes(points.size(), 1);

    gcode_instruction g3(0);
    g3.add_argument('G', 3);
    g3.add_argument('X', points.back().x);
    g3.add_argument('Y', points.back().y);
    g3.add_argument('R', 40);

    std::vector<printer_instruction> expected = moves(points, modes);
    printer_parser test_object(std::vector<gcode_instruction>({g3}), points[0]);
    // when
    test_object.parse();
    // then
    ASSERT_EQ(6, test_object.instructions().size());
    EXPECT_EQ(expected, test_object.instructions());
}

TEST(PrinterParserTest, parse_whenDestinationPointSameAsStarting_thenNoInstructions)
{
    // given
    vec point(10, 10);
    gcode_instruction g1(0);
    g1.add_argument('G', 1);
    g1.add_argument('X', point.x);
    g1.add_argument('Y', point.y);

    printer_parser test_object(std::vector<gcode_instruction>({g1}), point);
    // when
    test_object.parse();
    // then
    EXPECT_TRUE(test_object.instructions().empty());
}

TEST(PrinterParserTest, parse_whenMultipleInstructions_thenInstructionList)
{
    // given
    std::vector<vec> points = {vec(10, 10), vec(10, 10), vec(20, 20)};
    std::vector<int> modes = {0, 0, 1};

    gcode_instruction g0(0);
    g0.add_argument('G', 0);
    g0.add_argument('X', points[1].x);
    g0.add_argument('Y', points[1].y);

    gcode_instruction g1(1);
    g1.add_argument('G', 1);
    g1.add_argument('X', points[2].x);
    g1.add_argument('Y', points[2].y);

    std::vector<printer_instruction> expected = moves(points, modes);
    printer_parser test_object(std::vector<gcode_instruction>({g0, g1}), points[0]);
    // when
    test_object.parse();
    // then
    ASSERT_EQ(1, test_object.instructions().size());
    EXPECT_EQ(expected, test_object.instructions());
}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>
#include <vector>
#include <string>
#include "Puzzles.h"
#include "Puzzle01Part1Data.h"
#include "Puzzle02Part1Data.h"
#include "Puzzle03Part1Data.h"
#include "Puzzle04Part1Data.h"
#include "Puzzle08Part1Data.h"



void puzzle_01_part1_example()
{
  const auto input =
    std::vector<std::tuple<int,int>>
    {
        std::make_tuple(3,4)
        ,std::make_tuple(4,3)
        ,std::make_tuple(2,5)
        ,std::make_tuple(1,3)
        ,std::make_tuple(3,9)
        ,std::make_tuple(3,3)
    };

    const auto name = std::string("Historian Hysteria: Example");

    const auto output = puzzle_01::puzzle_01_part1(input);
    puzzle_report(1, 1, name, input, output);
}

void puzzle_01_part1_example_istream_read()
{
  using namespace std::string_literals;

  auto input = 
    "3 4\n"
    "4 3\n"
    "2 5\n"
    "1 3\n"
    "3 9\n"
    "3 3\n"s;

    const auto name = std::string("Historian Hysteria: Example, istream read");
    const auto output = puzzle_01::puzzle_01_part1_istream_read(std::move(input));    

    puzzle_report(1, 1, name, input, output);
}

void puzzle_01_part1_test()
{
    const auto input = puzzle_01_part1_data;
    const auto name = std::string("Historian Hysteria: Test");

    const auto output = puzzle_01::puzzle_01_part1(input);
    puzzle_report(1, 1, name, input, output);
}

void puzzle_01_part2_example()
{
  const auto input =
    std::vector<std::tuple<int,int>>
    {
        std::make_tuple(3,4)
        ,std::make_tuple(4,3)
        ,std::make_tuple(2,5)
        ,std::make_tuple(1,3)
        ,std::make_tuple(3,9)
        ,std::make_tuple(3,3)
    };

    const auto name = std::string("Historian Hysteria: Example");

    const auto output = puzzle_01::puzzle_01_part2(input);
    puzzle_report(1, 2, name, input, output);
}


void puzzle_01_part2_test()
{
    const auto input = puzzle_01_part1_data;

    const auto name = std::string("Historian Hysteria: Test");

    const auto output = puzzle_01::puzzle_01_part2(input);
    puzzle_report(1, 2, name, input, output);
}


void puzzle_02_part1_example()
{
  const auto input =
    std::vector
    {
        std::vector{7, 6, 4, 2, 1}
        ,std::vector{1, 2, 7, 8, 9}
        ,std::vector{9, 7, 6, 2, 1}
        ,std::vector{1, 3, 2, 4, 5}
        ,std::vector{8, 6, 4, 4, 1}
        ,std::vector{1, 3, 6, 7, 9}
    };

    const auto name = std::string("Red-Nosed Reports: Example");

    const auto output = puzzle_02::puzzle_02_part1(input);
    puzzle_report(2, 1, name, input, output);
}

void puzzle_02_part1_test()
{
    const auto input = puzzle_02_part1_data;

    const auto name = std::string("Red-Nosed Reports: Test");

    const auto output = puzzle_02::puzzle_02_part1(input);
    puzzle_report(2, 1, name, input, output);
}


void puzzle_02_part2_example()
{
  const auto input =
    std::vector
    {
        std::vector{7, 6, 4, 2, 1}
        ,std::vector{1, 2, 7, 8, 9}
        ,std::vector{9, 7, 6, 2, 1}
        ,std::vector{1, 3, 2, 4, 5}
        ,std::vector{8, 6, 4, 4, 1}
        ,std::vector{1, 3, 6, 7, 9}
    };

    const auto name = std::string("Red-Nosed Reports: Example");

    const auto output = puzzle_02::puzzle_02_part2(input);
    puzzle_report(2, 2, name, input, output);
}

void puzzle_02_part2_test()
{
    const auto input = puzzle_02_part1_data;

    const auto name = std::string("Red-Nosed Reports: Test");

    const auto output = puzzle_02::puzzle_02_part2(input);
    puzzle_report(2, 2, name, input, output);
}



void puzzle_03_part1_example()
{
  const std::string input = 
    "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

  const auto name = std::string("Mull It Over: Example");

  const auto output = puzzle_03::puzzle_03_part1(input);
  puzzle_report(3, 1, name, input, output);
}

void puzzle_03_part1_test()
{
  const auto input = puzzle_03_part1_data;

  const auto name = std::string("Mull It Over: Test");

  const auto output = puzzle_03::puzzle_03_part1(input);
  puzzle_report(3, 1, name, input, output);
}



void puzzle_03_part2_example()
{
  const std::string input = 
    "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";

  const auto name = std::string("Mull It Over: Example");

  const auto output = puzzle_03::puzzle_03_part2(input);
  puzzle_report(3, 2, name, input, output);
}

void puzzle_03_part2_test()
{
  const auto input = puzzle_03_part1_data;

  const auto name = std::string("Mull It Over: Test");

  const auto output = puzzle_03::puzzle_03_part2(input);
  puzzle_report(3, 2, name, input, output);
}



void puzzle_04_part1_example()
{
  const auto input = std::vector{
    std::string("MMMSXXMASM")
    ,std::string("MSAMXMSMSA")
    ,std::string("AMXSXMAAMM")
    ,std::string("MSAMASMSMX")
    ,std::string("XMASAMXAMM")
    ,std::string("XXAMMXXAMA")
    ,std::string("SMSMSASXSS")
    ,std::string("SAXAMASAAA")
    ,std::string("MAMMMXMMMM")
    ,std::string("MXMXAXMASX")
  };

  const auto name = std::string("Ceres Search: Example");

  const auto output = puzzle_04::puzzle_04_part1(input);
  puzzle_report(4, 1, name, input, output);
}



void puzzle_04_part1_test()
{
  const auto input = puzzle_04_part1_data;

  const auto name = std::string("Ceres Search: Test");

  const auto output = puzzle_04::puzzle_04_part1(input);
  puzzle_report(4, 1, name, input, output);
}


void puzzle_04_part2_example()
{
  const auto input = std::vector{
    std::string("MMMSXXMASM")
    ,std::string("MSAMXMSMSA")
    ,std::string("AMXSXMAAMM")
    ,std::string("MSAMASMSMX")
    ,std::string("XMASAMXAMM")
    ,std::string("XXAMMXXAMA")
    ,std::string("SMSMSASXSS")
    ,std::string("SAXAMASAAA")
    ,std::string("MAMMMXMMMM")
    ,std::string("MXMXAXMASX")
  };

  const auto name = std::string("Ceres Search: Example");

  const auto output = puzzle_04::puzzle_04_part2(input);
  puzzle_report(4, 2, name, input, output);
}



void puzzle_04_part2_test()
{
  const auto input = puzzle_04_part1_data;

  const auto name = std::string("Ceres Search: Test");

  const auto output = puzzle_04::puzzle_04_part2(input);
  puzzle_report(4, 2, name, input, output);
}


void puzzle_08_part1_example()
{
  const auto input = std::vector{
     std::string("............")
    ,std::string("........0...")
    ,std::string(".....0......")
    ,std::string(".......0....")
    ,std::string("....0.......")
    ,std::string("......A.....")
    ,std::string("............")
    ,std::string("............")
    ,std::string("........A...")
    ,std::string(".........A..")
    ,std::string("............")
    ,std::string("............")
  };

  const auto name = std::string("Resonant Collinearity: Example");

  const auto output = puzzle_08::puzzle_08_part1(input);
  puzzle_report(8, 1, name, input, output);
}



void puzzle_08_part1_test()
{
  const auto input = puzzle_08_part1_data;

  const auto name = std::string("Resonant Collinearity: Test");

  const auto output = puzzle_08::puzzle_08_part1(input);
  puzzle_report(8, 1, name, input, output);
}


int main(int,char*[])
{
  //puzzle_01_part1_example();
  //puzzle_01_part1_example_istream_read();
  //puzzle_01_part1_test();
  //puzzle_01_part2_example();
  //puzzle_01_part2_test();

  //puzzle_02_part1_example();
  //puzzle_02_part1_test();
  //puzzle_02_part2_example();
  //puzzle_02_part2_test();

  //puzzle_03_part1_example();
  //puzzle_03_part1_test();
  //puzzle_03_part2_example();
  //puzzle_03_part2_test();

  //puzzle_04_part1_example();
  //puzzle_04_part1_test();
  //puzzle_04_part2_example();
  //puzzle_04_part2_test();

  //puzzle_08_part1_example();
  puzzle_08_part1_test();
  //puzzle_08_part2_example();
  //puzzle_08_part2_test();

  return 0;
}


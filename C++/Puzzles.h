#ifndef PUZZLES_H
#define PUZZLES_H

#include <iostream>
#include <vector>
#include <string>
#include "iostreamext.h"

template <typename I,typename O>
void puzzle_report(const int puzzle_number,const int puzzle_part, const std::string& puzzle_name, const I& input, const O& output)
{
  std::cout << std::endl;
  std::cout << "==========================================================" << std::endl;
  std::cout << "Puzzle Number: " << puzzle_number << " | Part:" << puzzle_part << std::endl;
  std::cout << "  Puzzle Name: " << puzzle_name << std::endl;
  std::cout << "----------------------------------------------------------" << std::endl;
  std::cout << "Input: " << std::endl;
  std::cout << input << std::endl;
  std::cout << "----------------------------------------------------------" << std::endl;
  std::cout << "Result: " << std::endl;
  std::cout << output << std::endl;
  std::cout << "==========================================================" << std::endl;
  std::cout << std::endl;
}

namespace puzzle_01
{
  int puzzle_01_part1(const std::vector<std::tuple<int,int>> &arbitrary_pairs);
  int puzzle_01_part2(const std::vector<std::tuple<int,int>> &arbitrary_pairs);

  int puzzle_01_part1_istream_read(std::string&& input_string);
}

namespace puzzle_02
{
  int puzzle_02_part1(const std::vector<std::vector<int>> &xss);
  int puzzle_02_part2(const std::vector<std::vector<int>> &xss);
}

namespace puzzle_03
{
  int puzzle_03_part1(const std::string& memory);
  int puzzle_03_part2(const std::string& memory);
}

namespace puzzle_04
{
  int puzzle_04_part1(const std::vector<std::string>& grid);
  int puzzle_04_part2(const std::vector<std::string>& grid); 
}


namespace puzzle_08
{
  int puzzle_08_part1(const std::vector<std::string>& grid);
  int puzzle_08_part2(const std::vector<std::string>& grid); 
}

#endif //PUZZLES_H

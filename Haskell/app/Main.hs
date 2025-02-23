module Main (main) where

import Control.Monad

import Puzzles
import Puzzle_01_Part1_Data
import Puzzle_02_Part1_Data
import Puzzle_03_Part1_Data
import Puzzle_04_Part1_Data

puzzle_01_part1_example :: IO ()
puzzle_01_part1_example = do
  let
    input = 
      [
         (3,   4)
        ,(4,   3)
        ,(2,   5)
        ,(1,   3)
        ,(3,   9)
        ,(3,   3)
      ]
    output = puzzle_01_part1 input
  puzzle_report 1 1 "Historian Hysteria: Example" input output

puzzle_01_part1_test :: IO ()
puzzle_01_part1_test = do
  let
    input = puzzle_01_part1_input_data
    output = puzzle_01_part1 input
  puzzle_report 1 1 "Historian Hysteria: Test" input output

puzzle_01_part2_example :: IO ()
puzzle_01_part2_example = do
  let
    input = 
      [
         (3,   4)
        ,(4,   3)
        ,(2,   5)
        ,(1,   3)
        ,(3,   9)
        ,(3,   3)
      ]
    output = puzzle_01_part2 input
  puzzle_report 1 2 "Historian Hysteria: Example" input output

puzzle_01_part2_test :: IO ()
puzzle_01_part2_test = do
  let
    input = puzzle_01_part1_input_data
    output = puzzle_01_part2 input
  puzzle_report 1 2 "Historian Hysteria: Test" input output



puzzle_02_part1_example :: IO ()
puzzle_02_part1_example = do
  let
    input = 
      [
        [7, 6, 4, 2, 1]
        ,[1, 2, 7, 8, 9]
        ,[9, 7, 6, 2, 1]
        ,[1, 3, 2, 4, 5]
        ,[8, 6, 4, 4, 1]
        ,[1, 3, 6, 7, 9]
      ]
    output = puzzle_02_part1 input
  puzzle_report 2 1 "Red-Nosed Reports: Example" input output


puzzle_02_part1_test :: IO ()
puzzle_02_part1_test = do
  let
    input = puzzle_02_part1_input_data
    output = puzzle_02_part1 input
  puzzle_report 2 1 "Red-Nosed Reports: Test" input output


puzzle_02_part2_example :: IO ()
puzzle_02_part2_example = do
  let
    input = 
      [
        [7, 6, 4, 2, 1]
        ,[1, 2, 7, 8, 9]
        ,[9, 7, 6, 2, 1]
        ,[1, 3, 2, 4, 5]
        ,[8, 6, 4, 4, 1]
        ,[1, 3, 6, 7, 9]
      ]
    output = puzzle_02_part2 input
  puzzle_report 2 2 "Red-Nosed Reports: Example" input output


puzzle_02_part2_test :: IO ()
puzzle_02_part2_test = do
  let
    input = puzzle_02_part1_input_data
    output = puzzle_02_part2 input
  puzzle_report 2 2 "Red-Nosed Reports: Test" input output


puzzle_03_part1_example :: IO ()
puzzle_03_part1_example = do
  let
    input = 
      "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"
    output = puzzle_03_part1 input
  puzzle_report 3 1 "Mull It Over: Example" input output


puzzle_03_part1_test :: IO ()
puzzle_03_part1_test = do
  let
    input = 
      puzzle_03_part1_input_data
    output = puzzle_03_part1 input
  puzzle_report 3 1 "Mull It Over: Test" input output


puzzle_03_part2_example :: IO ()
puzzle_03_part2_example = do
  let
    input = 
      "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"
    output = puzzle_03_part2 input
  puzzle_report 3 2 "Mull It Over: Example" input output


puzzle_03_part2_test :: IO ()
puzzle_03_part2_test = do
  let
    input = 
      puzzle_03_part1_input_data
    output = puzzle_03_part2 input
  puzzle_report 3 2 "Mull It Over: Test" input output


puzzle_04_part1_example :: IO ()
puzzle_04_part1_example = do
  let
    input = 
      ["MMMSXXMASM"
      ,"MSAMXMSMSA"
      ,"AMXSXMAAMM"
      ,"MSAMASMSMX"
      ,"XMASAMXAMM"
      ,"XXAMMXXAMA"
      ,"SMSMSASXSS"
      ,"SAXAMASAAA"
      ,"MAMMMXMMMM"
      ,"MXMXAXMASX"]
    output = puzzle_04_part1 input
  puzzle_report 4 1 "Ceres Search: Example" input output


puzzle_04_part1_test :: IO ()
puzzle_04_part1_test = do
  let
    input = 
      puzzle_04_part1_input_data
    output = puzzle_04_part1 input
  puzzle_report 4 2 "Ceres Search: Test" input output


puzzle_04_part2_example :: IO ()
puzzle_04_part2_example = do
  let
    input = 
      ["MMMSXXMASM"
      ,"MSAMXMSMSA"
      ,"AMXSXMAAMM"
      ,"MSAMASMSMX"
      ,"XMASAMXAMM"
      ,"XXAMMXXAMA"
      ,"SMSMSASXSS"
      ,"SAXAMASAAA"
      ,"MAMMMXMMMM"
      ,"MXMXAXMASX"]
    output = puzzle_04_part2 input
  puzzle_report 4 2 "Ceres Search: Example" input output


puzzle_04_part2_test :: IO ()
puzzle_04_part2_test = do
  let
    input = 
      puzzle_04_part1_input_data
    output = puzzle_04_part2 input
  puzzle_report 4 2 "Ceres Search: Test" input output



puzzle_05_part1_example :: IO ()
puzzle_05_part1_example = do
  input <- readFile "src/Puzzle_05_Part1_example.txt"
  let
    output = puzzle_05_part1 input
  puzzle_report 5 1 "Print Queue: Example" input output


puzzle_05_part1_test :: IO ()
puzzle_05_part1_test = do
  input <- readFile "src/Puzzle_05_Part1_test.txt"
  let
    output = puzzle_05_part1 input
  puzzle_report 5 1 "Print Queue: Test" input output


puzzle_05_part2_example :: IO ()
puzzle_05_part2_example = do
  input <- readFile "src/Puzzle_05_Part1_example.txt"
  let
    output = puzzle_05_part2 input
  puzzle_report 5 2 "Print Queue: Example" input output


puzzle_05_part2_test :: IO ()
puzzle_05_part2_test = do
  input <- readFile "src/Puzzle_05_Part1_test.txt"
  let
    output = puzzle_05_part2 input
  puzzle_report 5 2 "Print Queue: Test" input output


puzzle_07_part1_example :: IO ()
puzzle_07_part1_example = do
  let
    input =
      [
        "190: 10 19"
        ,"3267: 81 40 27"
        ,"83: 17 5"
        ,"156: 15 6"
        ,"7290: 6 8 6 15"
        ,"161011: 16 10 13"
        ,"192: 17 8 14"
        ,"21037: 9 7 18 13"
        ,"292: 11 6 16 20"
      ]
    output = puzzle_07_part1 input
  puzzle_report 7 1 "Bridge Repair: Example" input output


puzzle_07_part1_test :: IO ()
puzzle_07_part1_test = do
  input <- liftM lines . readFile $ "src/Puzzle_07_Part1_test.txt"
  let
    output = puzzle_07_part1 input
  puzzle_report 7 1 "Bridge Repair: Test" input output


puzzle_07_part2_example :: IO ()
puzzle_07_part2_example = do
  let
    input =
      [
        "190: 10 19"
        ,"3267: 81 40 27"
        ,"83: 17 5"
        ,"156: 15 6"
        ,"7290: 6 8 6 15"
        ,"161011: 16 10 13"
        ,"192: 17 8 14"
        ,"21037: 9 7 18 13"
        ,"292: 11 6 16 20"
      ]
    output = puzzle_07_part2 input
  puzzle_report 7 2 "Bridge Repair: Example" input output


puzzle_07_part2_test :: IO ()
puzzle_07_part2_test = do
  input <- liftM lines . readFile $ "src/Puzzle_07_Part1_test.txt"
  let
    output = puzzle_07_part2 input
  puzzle_report 7 2 "Bridge Repair: Test" input output


puzzle_07_extended_example :: IO ()
puzzle_07_extended_example = do
  let
    input =
      [
        "190: 10 19"
        ,"3267: 81 40 27"
        ,"83: 17 5"
        ,"156: 15 6"
        ,"7290: 6 8 6 15"
        ,"161011: 16 10 13"
        ,"192: 17 8 14"
        ,"21037: 9 7 18 13"
        ,"292: 11 6 16 20"
      ]
    output = puzzle_07_extended input
  puzzle_report 7 3 "Bridge Repair: Example" input output


puzzle_07_extended_test :: IO ()
puzzle_07_extended_test = do
  input <- liftM lines . readFile $ "src/Puzzle_07_Part1_test.txt"
  let
    output = puzzle_07_extended input
  puzzle_report 7 3 "Bridge Repair: Test" input output



main :: IO ()
main = do
  --puzzle_01_part1_example
  --puzzle_01_part1_test
  --puzzle_01_part2_example
  --puzzle_01_part2_test

  --puzzle_02_part1_example
  --puzzle_02_part1_test
  --puzzle_02_part2_example
  --puzzle_02_part2_test

  --puzzle_03_part1_example
  --puzzle_03_part1_test
  --puzzle_03_part2_example
  --puzzle_03_part2_test

  --puzzle_04_part1_example
  --puzzle_04_part1_test
  --puzzle_04_part2_example
  --puzzle_04_part2_test

  --puzzle_05_part1_example
  --puzzle_05_part1_test
  --puzzle_05_part2_example
  --puzzle_05_part2_test

  --puzzle_07_part1_example
  --puzzle_07_part1_test
  --puzzle_07_part2_example
  --puzzle_07_part2_test
  --puzzle_07_extended_example
  puzzle_07_extended_test


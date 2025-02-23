
//use std::fmt::Display;
use std::fmt::Debug;

pub fn report<I : Debug,O : Debug>(puzzle_number : i32, puzzle_part : i32, puzzle_name : &str, input : &I, output : &O)
{
    println!("");
    println!("==========================================================");
    println!("Puzzle Number: {puzzle_number} | Part: {puzzle_part}");
    println!("  Puzzle Name: {puzzle_name}");
    println!("----------------------------------------------------------");
    println!("Input: ");
    println!("{input:?}");
    println!("----------------------------------------------------------");
    println!("Output: ");
    println!("{output:?}");
    println!("==========================================================");
}



//#![feature(closure_lifetime_binder)]

pub mod utils;
pub mod puzzles;
pub mod puzzle_data;

use utils::puzzle_utils;

//use utils::graph_utils;

/*
puzzle_report :: (Show input, Show output) => Int -> Int -> String -> input -> output -> IO ()
puzzle_report puzzle_number puzzle_part puzzle_name input output = do
    putStrLn ""
    putStrLn "=========================================================="
    putStrLn $ "Puzzle Number: " ++ show puzzle_number ++ " | Part:" ++ show puzzle_part
    putStrLn $ "  Puzzle Name: " ++ show puzzle_name
    putStrLn "----------------------------------------------------------"
    putStrLn "Input: "
    putStrLn $ show input
    putStrLn "----------------------------------------------------------"
    putStrLn "Result: "
    putStrLn $ show output
    putStrLn "=========================================================="
    putStrLn ""
*/




fn puzzle_05_part1_example() 
{
  let input_ordering_pairs= vec![
     (7,53)
    ,(97,13)
    ,(97,61)
    ,(97,47)
    ,(75,29)
    ,(61,13)
    ,(75,53)
    ,(29,13)
    ,(97,29)
    ,(53,29)
    ,(61,53)
    ,(97,53)
    ,(61,29)
    ,(47,13)
    ,(75,47)
    ,(97,75)
    ,(47,61)
    ,(75,61)
    ,(47,29)
    ,(75,13)
    ,(53,13)];
  let input_update_sequences = vec![
     vec![75,47,61,53,29]
    ,vec![97,61,53,29,13]
    ,vec![75,29,13]
    ,vec![75,97,47,61,53]
    ,vec![61,13,29]
    ,vec![97,13,75,29,47]];

  let output = puzzles::puzzle_05_part1(&input_ordering_pairs,&input_update_sequences);
  puzzle_utils::report(5,1,"Print Queue: Example",&(&input_ordering_pairs,&input_update_sequences),&output);
}


fn puzzle_05_part1_test() 
{
  let input_ordering_pairs = puzzle_data::puzzle_05_part1_test::input_ordering_pairs();
  let input_update_sequences = puzzle_data::puzzle_05_part1_test::input_update_sequences();
  
  let output = puzzles::puzzle_05_part1(&input_ordering_pairs,&input_update_sequences);
  puzzle_utils::report(5,1,"Print Queue: Test",&(&input_ordering_pairs,&input_update_sequences),&output);
}



fn puzzle_05_part2_example() 
{
  let input_ordering_pairs= vec![
     (7,53)
    ,(97,13)
    ,(97,61)
    ,(97,47)
    ,(75,29)
    ,(61,13)
    ,(75,53)
    ,(29,13)
    ,(97,29)
    ,(53,29)
    ,(61,53)
    ,(97,53)
    ,(61,29)
    ,(47,13)
    ,(75,47)
    ,(97,75)
    ,(47,61)
    ,(75,61)
    ,(47,29)
    ,(75,13)
    ,(53,13)];
  let input_update_sequences = vec![
     vec![75,47,61,53,29]
    ,vec![97,61,53,29,13]
    ,vec![75,29,13]
    ,vec![75,97,47,61,53]
    ,vec![61,13,29]
    ,vec![97,13,75,29,47]];

  let output = puzzles::puzzle_05_part2(&input_ordering_pairs,&input_update_sequences);
  puzzle_utils::report(5,2,"Print Queue: Example",&(&input_ordering_pairs,&input_update_sequences),&output);
}


fn puzzle_05_part2_test() 
{
  let input_ordering_pairs = puzzle_data::puzzle_05_part1_test::input_ordering_pairs();
  let input_update_sequences = puzzle_data::puzzle_05_part1_test::input_update_sequences();
  
  let output = puzzles::puzzle_05_part2(&input_ordering_pairs,&input_update_sequences);
  puzzle_utils::report(5,2,"Print Queue: Test",&(&input_ordering_pairs,&input_update_sequences),&output);
}



fn puzzle_06_part1_example() 
{
  let input = vec![
     "....#....."
    ,".........#"
    ,".........."
    ,"..#......."
    ,".......#.."
    ,".........."
    ,".#..^....."
    ,"........#."
    ,"#........."
    ,"......#..."];
  let output = puzzles::puzzle_06_part1(&input);
  puzzle_utils::report(6,1,"Print Queue: Example",&input,&output);
}


fn puzzle_06_part1_test() 
{
  let input = puzzle_data::puzzle_06_part1_test::input();
  
  let output = puzzles::puzzle_06_part1(&input);
  puzzle_utils::report(6,1,"Print Queue: Test",&input,&output);
}




fn puzzle_06_part2_example() 
{
  let input = vec![
     "....#....."
    ,".........#"
    ,".........."
    ,"..#......."
    ,".......#.."
    ,".........."
    ,".#..^....."
    ,"........#."
    ,"#........."
    ,"......#..."];
  let output = puzzles::puzzle_06_part2(&input);
  puzzle_utils::report(6,2,"Print Queue: Example",&input,&output);
}


fn puzzle_06_part2_test() 
{
  let input = puzzle_data::puzzle_06_part1_test::input();
  
  let output = puzzles::puzzle_06_part2(&input);
  puzzle_utils::report(6,2,"Print Queue: Test",&input,&output);
}



fn main() {
    println!("Starting...");

    //graph_utils::debug_main();
    
    //puzzle_05_part1_example();
    //puzzle_05_part1_test();
    //puzzle_05_part2_example();
    //puzzle_05_part2_test();

    //puzzle_06_part1_example();
    //puzzle_06_part1_test();
    //puzzle_06_part2_example();
    puzzle_06_part2_test();

}

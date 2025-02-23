module PuzzleUtils
  (puzzle_report) where


puzzle_report :: (Show input, Show output) => Int -> Int -> String -> input -> output -> IO ()
puzzle_report puzzle_number puzzle_part puzzle_name input output = do
    putStrLn ""
    putStrLn "=========================================================="
    putStrLn $ "Puzzle Number: " ++ show puzzle_number ++ " | Part: " ++ show puzzle_part
    putStrLn $ "  Puzzle Name: " ++ show puzzle_name
    putStrLn "----------------------------------------------------------"
    putStrLn "Input: "
    putStrLn $ show input
    putStrLn "----------------------------------------------------------"
    putStrLn "Result: "
    putStrLn $ show output
    putStrLn "=========================================================="
    putStrLn ""


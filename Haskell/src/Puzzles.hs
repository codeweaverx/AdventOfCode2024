module Puzzles
    ( 
        puzzle_report
        ,puzzle_01_part1
        ,puzzle_01_part2
        ,puzzle_02_part1
        ,puzzle_02_part2
        ,puzzle_03_part1
        ,puzzle_03_part2
        ,puzzle_04_part1
        ,puzzle_04_part2
        ,puzzle_05_part1
        ,puzzle_05_part2
        ,puzzle_07_part1
        ,puzzle_07_part2
        ,puzzle_07_extended
    ) where

import Control.Monad
import Data.List
import Data.List.Split
import Data.List.Utils
import Data.List.Extra
import qualified Data.Vector as V
import qualified Data.Map as M
import qualified Data.Set as S
import Data.Char
import Data.Maybe
import System.IO.Unsafe
import Text.Regex.TDFA
import Text.Read

import PuzzleUtils
import ListUtils
import GraphUtils

-- Historian Hysteria P1
puzzle_01_part1 :: [(Int,Int)] -> Int
puzzle_01_part1 arbitrary_pairs =
    distance
  where
    (list1,list2) = unzip arbitrary_pairs
    [sorted_list1,sorted_list2] = map sort [list1,list2]
    aligned_pairs = zip sorted_list1 sorted_list2
    distance = foldl1' (+) . map (\(x,y) -> abs(x-y)) $ aligned_pairs


-- Historian Hysteria P2
puzzle_01_part2 :: [(Int,Int)] -> Int
puzzle_01_part2 arbitrary_pairs =
    distance
  where
    (list1,list2) = unzip arbitrary_pairs
    histogram = foldl' (\acc x -> M.insertWith (+) x 1 acc) M.empty list2
    distance = foldl1' (+) . map (\i -> i * M.findWithDefault 0 i histogram) $ list1


-- Red-Nosed Reports P1
puzzle_02_part1 :: [[Int]] -> Int
puzzle_02_part1 xss = length . filter id . map puzzle_02_part1_one_line $ xss

puzzle_02_part1_one_line [] = undefined
puzzle_02_part1_one_line [x] = True
puzzle_02_part1_one_line xs@(x0:y0:_) = 
    all good $ zip xs (tail xs)
  where
    cmp = if (x0>y0) then (>) else if (x0<y0) then (<) else \_ _ -> False
    good_relation cmp x y = abs(x-y)<=3 && cmp x y
    good = uncurry . good_relation $ cmp


-- Red-Nosed Reports P2
puzzle_02_part2 :: [[Int]] -> Int
puzzle_02_part2 xss = length . filter id . map puzzle_02_part2_one_line $ xss


puzzle_02_part2_one_line [] = undefined
puzzle_02_part2_one_line [x] = True
puzzle_02_part2_one_line xs = 
    or all_variants
  where
    n = length xs
    all_variants = 
        map puzzle_02_part1_one_line 
        . map (flip remove_nth xs) 
        $ [0..n-1]


-- Mull It Over P1
puzzle_03_part1 :: String -> Int
puzzle_03_part1 s = 
    foldl' (+) 0 . map (\(x,y) -> x*y ) $ mull_pairs
  where
    regex = "mul\\(([[:digit:]]{1,3}),([[:digit:]]{1,3})\\)"
    find_mul_with_remainder :: String -> Maybe ((Int,Int),String)
    find_mul_with_remainder s' = let (_,_,after,digits) = ((s' =~ regex) :: (String,String,String,[String])) in if null digits then Nothing else Just ((read.head$digits, read.head.tail$digits),after)
    mull_pairs = unfoldr find_mul_with_remainder s



-- Mull It Over P2

matches :: String -> String -> (String,String,String,[String])
matches = (=~)

puzzle_03_part2 :: String -> Int
puzzle_03_part2 input = 
    foldl' (+) 0 . map (\[(x,y)] -> x*y ) . filter (not.null) $ mull_pairs
  where
    regex = "(mul\\(([[:digit:]]{1,3}),([[:digit:]]{1,3})\\))|(do\\(\\))|(don't\\(\\))" :: String
    match_maker s = matches s regex
    find_commands_with_remainder (b,s) = let (_,cmd,after,groups) = s `matches` regex in 
        match cmd groups after
      where
        match ('d':'o':'(':_) _ after = Just ([],(True,after))
        match ('d':'o':'n':_) _ after = Just ([],(False,after))
        match ('m':'u':'l':_) [_,numStr1,numStr2,_,_] after = Just (if b then [(read numStr1,read numStr2)] else [],(b,after))
        match _ _ _ = Nothing
    mull_pairs = unfoldr find_commands_with_remainder (True,input)

-- Ceres Search P1

puzzle_04_part1 :: [String] -> Int
puzzle_04_part1 input= 
  puzzle_04_part1_search_grid g
    where
  g = V.fromList . map V.fromList $ input

type Row = V.Vector Char
type Grid = V.Vector Row
type P2 = (Int,Int)
type V2 = (Int,Int)

p2_plus_v2 :: P2 -> V2 -> P2
p2_plus_v2 (x,y) (dx,dy) = (x+dx, y+dy)

puzzle_04_part1_search_grid :: Grid -> Int
puzzle_04_part1_search_grid g = 
    result
  where
    regex = "XMAS"
    h = V.length g
    w = if h<=0 then 0 else V.length (g V.! 0)
    result = foldl' (+) 0 
      [
        {-  row_forward_cases = -}        foldl' (+) 0 . map (\j -> (puzzle_04_line_string g (0,j) (1,0) =~ regex) :: Int) $ [0..h-1]
        ,{- row_backward_cases = -}       foldl' (+) 0 . map (\j -> (puzzle_04_line_string g (w-1,j) (-1,0) =~ regex) :: Int) $ [0..h-1]
        ,{- col_forward_cases = -}        foldl' (+) 0 . map (\i -> (puzzle_04_line_string g (i,0) (0,1) =~ regex) :: Int) $ [0..w-1]
        ,{- col_backward_cases = -}       foldl' (+) 0 . map (\i -> (puzzle_04_line_string g (i,h-1) (0,-1) =~ regex) :: Int) $ [0..w-1]
        ,{- top_diag_leftward_cases = -}  foldl' (+) 0 . map (\i -> (puzzle_04_line_string g (i,0) (-1,1) =~ regex) :: Int) $ [0..w-1]
        ,{- top_diag_rightward_cases = -} foldl' (+) 0 . map (\i -> (puzzle_04_line_string g (i,0) (1,1) =~ regex) :: Int) $ [0..w-1]
        ,{- bot_diag_leftward_cases = -}  foldl' (+) 0 . map (\i -> (puzzle_04_line_string g (i,h-1) (-1,-1) =~ regex) :: Int) $ [0..w-1]
        ,{- bot_diag_rightward_cases = -} foldl' (+) 0 . map (\i -> (puzzle_04_line_string g (i,h-1) (1,-1) =~ regex) :: Int) $ [0..w-1]
        ,{- lft_diag_upward_cases = -}    foldl' (+) 0 . map (\j -> (puzzle_04_line_string g (0,j) (1,-1) =~ regex) :: Int) $ [1..h-2]
        ,{- lft_diag_downward_cases = -}  foldl' (+) 0 . map (\j -> (puzzle_04_line_string g (0,j) (1,1) =~ regex) :: Int) $ [1..h-2]
        ,{- rgt_diag_upward_cases = -}    foldl' (+) 0 . map (\j -> (puzzle_04_line_string g (w-1,j) (-1,-1) =~ regex) :: Int) $ [1..h-2]
        ,{- rgt_diag_downward_cases = -}  foldl' (+) 0 . map (\j -> (puzzle_04_line_string g (w-1,j) (-1,1) =~ regex) :: Int) $ [1..h-2]
      ]

puzzle_04_line_string :: Grid -> P2 -> V2 -> String
puzzle_04_line_string g p v =
    str
  where
    h = V.length g
    w = if h<=0 then 0 else V.length (g V.! 0)
    in_bounds (x,y) = x>=0 && x<w && y>=0 && y<h
    ps = takeWhile in_bounds . iterate (flip p2_plus_v2 v) $ p
    str = map (\(i,j) -> (g V.! j) V.! i) ps




puzzle_04_part2 :: [String] -> Int
puzzle_04_part2 input= 
  puzzle_04_part2_search_grid g
    where
  g = V.fromList . map V.fromList $ input


puzzle_04_part2_search_grid :: Grid -> Int
puzzle_04_part2_search_grid g = 
    foldl' (\acc j -> acc + foldl' (\acc i -> acc + puzzle_04_match_string_in_cross_rotations g (i,j) "AMMSS") 0 [1..w-2]) 0 [1..h-2]
  where
    h = V.length g
    w = if h<=0 then 0 else V.length (g V.! 0)

puzzle_04_match_string_in_cross_rotations :: Grid -> P2 -> [Char] -> Int
puzzle_04_match_string_in_cross_rotations g p (c:cs) = 
    foldl' (\acc cs' -> acc + if puzzle_04_match_string_in_cross g p (c:cs') then 1 else 0) 0 all_rotations
  where
    cyclical_cs = cycle cs
    overChunks = Data.List.Split.chunksOf 5 cyclical_cs
    trimmedChunks = map (take 4) overChunks
    all_rotations = take 4 trimmedChunks


puzzle_04_match_string_in_cross :: Grid -> P2 -> [Char] -> Bool
puzzle_04_match_string_in_cross g p cs = 
    and $ zipWith (puzzle_04_match_cell g) cs positions
  where
    deltas = [(0,0),(1,1), (-1,1),(-1,-1),(1,-1)]
    positions = map (p2_plus_v2 p) deltas

puzzle_04_match_cell :: Grid -> Char -> P2  -> Bool
puzzle_04_match_cell g c (i,j) = g V.! j V.! i == c




-- ------------------------
-- Puzzle 5: Print Queue
-- ------------------------
puzzle_05_part1 :: String -> Int
puzzle_05_part1 input = 
    puzzle_05_part1_solve orderingPairs updateSequences
  where
    (orderingPairs,updateSequences) = puzzle_05_part1_parse input

puzzle_05_part1_parse :: String -> ([(Int,Int)],[[Int]])
puzzle_05_part1_parse input =
    {-debugStr `seq`-} (orderingPairs,updateSequences)
  where
    -- debugStr = unsafePerformIO $ putStrLn $ show (orderingPairs,updateSequences)

    isBlankLine = null . filter (not . isSpace)

    ls = lines input
    (orderingLines,rest) = span (not . isBlankLine) . dropWhile isBlankLine $ ls
    (updateLines,_) = span (not.isBlankLine) . dropWhile (isBlankLine) $ rest
    

    orderingPairs :: [(Int,Int)]
    orderingPairs = mapMaybe maybeOrderingPair . map (splitOneOf "|") $ orderingLines
    maybeOrderingPair [ns0,ns1] = readMaybe ns0 >>= \n0 -> readMaybe ns1 >>= \n1 -> Just (n0,n1)
    maybeOrderingPair _ = Nothing

    updateSequences :: [[Int]]
    updateSequences = mapMaybe maybeSequence . map (splitOneOf ",") $ updateLines
    maybeSequence stringSequence = sequence . map readMaybe $ stringSequence

puzzle_05_part1_solve :: [(Int,Int)] -> [[Int]] -> Int
puzzle_05_part1_solve orderingPairs updateSequences =
  foldl' (+) 0 . catMaybes $ maybeMiddlePages
    where
  maybeMiddlePages = map (puzzle_05_part1_solve_one orderingPairs) updateSequences

puzzle_05_part1_solve_one :: [(Int,Int)] -> [Int] -> Maybe Int
puzzle_05_part1_solve_one orderingPairs updateSequence =
    maybeMiddlePage
  -- debugStr `seq` maybeMiddlePage
  where
  -- debugStr = unsafePerformIO $ putStrLn $ unlines $ [show usefulPairs, show pairsFromUpdateSequences, show edges]

    sequenceSet = S.fromList updateSequence
    usefulPairs = filter (\(from,to) -> S.member from sequenceSet && S.member to sequenceSet) orderingPairs
    pairsFromUpdateSequences = zip updateSequence (tail updateSequence)

    testPairs = usefulPairs ++ pairsFromUpdateSequences
    edges = graphutils_edge_map_from_edges testPairs

    canSort = isJust . topological_sort updateSequence $ edges

    maybeMiddlePage = if canSort then Just . head . drop (length updateSequence `div` 2) $ updateSequence else Nothing



puzzle_05_part2 :: String -> Int
puzzle_05_part2 input = 
    puzzle_05_part2_solve orderingPairs updateSequences
  where
    (orderingPairs,updateSequences) = puzzle_05_part1_parse input


puzzle_05_part2_solve :: [(Int,Int)] -> [[Int]] -> Int
puzzle_05_part2_solve orderingPairs updateSequences =
  foldl' (+) 0 . catMaybes $ madeSolveables
    where
  maybeSolveables = zip updateSequences $ map (puzzle_05_part1_solve_one orderingPairs) updateSequences
  unsolveables = map fst . filter (\(_,result) -> isNothing result) $ maybeSolveables
  madeSolveables = map (puzzle_05_part2_solve_one orderingPairs) unsolveables


puzzle_05_part2_solve_one :: [(Int,Int)] -> [Int] -> Maybe Int
puzzle_05_part2_solve_one orderingPairs updateSequence =
    maybeMiddlePage
    --debugStr `seq` maybeMiddlePage
  where
    --debugStr = unsafePerformIO $ putStrLn $ unlines $ [show updateSequence,show edges,show sortings]

    sequenceSet = S.fromList updateSequence
    usefulPairs = filter (\(from,to) -> S.member from sequenceSet && S.member to sequenceSet) orderingPairs
    edges = graphutils_edge_map_from_edges usefulPairs

    sortings = topological_sort updateSequence $ edges

    maybeMiddlePage = sortings >>= \xs -> Just . head . drop (length xs `div` 2) $ xs


puzzle_07_part1 :: [String] -> Int
puzzle_07_part1 ss =
    result
  where
    puzzles = map puzzle_07_parse_puzzle ss
    result = puzzle_07_solve puzzles puzzle_07_part1_ops

puzzle_07_part1_ops :: [Int->Int->Int]
puzzle_07_part1_ops = [(+),(*)]

puzzle_07_parse_puzzle :: String -> (Int,[Int])
puzzle_07_parse_puzzle s =
    (r,xs)
  where
    -- format is: "r: x x x ... x", thus pull r, skip :, and words out the rest
    [(r,(_:s'))] = reads s
    xs = map read . words $ s'

puzzle_07_solve :: [(Int,[Int])] -> [Int->Int->Int] -> Int
puzzle_07_solve puzzles ops =
    result
  where 
    rs = map fst puzzles
    operandss = map snd puzzles

    resultss = map (puzzle_07_all_results_on_operands ops) operandss
    successfuls = map fst . filter (\(r,result) -> any (==r) result) $ zip rs resultss

    result = foldl' (+) 0 successfuls

puzzle_07_all_results_on_operands :: [Int->Int->Int] -> [Int] -> [Int]
puzzle_07_all_results_on_operands ops operands =
    result
  where
    (v:vs) = operands
    fn y = \x -> map (\op -> x `op` y) ops
    fns = map fn vs
    master_fn = foldr1 (\acc f -> acc >=> f) fns

    -- note that no actual work on computing any results has occurred
    -- at any point.  We've just build a function that takes the first parameter.    
    
    result = master_fn v
    
    -- Even more interestingly, because of lazy evaluation, what
    -- we have produced is a list that can be expanded as needed.
    -- 'result' in C# or Rust would be an iterator owning all its own
    -- values for 'unfolding' into the singly linked list of results.

puzzle_07_part2 :: [String] -> Int
puzzle_07_part2 ss =
    result
  where
    puzzles = map puzzle_07_parse_puzzle ss
    result = puzzle_07_solve puzzles puzzle_07_part2_ops

puzzle_07_part2_ops :: [Int->Int->Int]
puzzle_07_part2_ops = [(+),(*),\x y->read (show x ++ show y)]


puzzle_07_extended :: [String] -> Int
puzzle_07_extended ss =
    result
  where
    puzzles = map puzzle_07_parse_puzzle ss
    result = puzzle_07_extended_solve puzzles puzzle_07_extended_ops

puzzle_07_extended_ops :: [Int->Int->Int]
puzzle_07_extended_ops = [(+),(*),(-),div,\x y->read (show x ++ show y)]


puzzle_07_extended_solve :: [(Int,[Int])] -> [Int->Int->Int] -> Int
puzzle_07_extended_solve puzzles ops =
    result
  where 
    rs = map fst puzzles
    operandss = map snd puzzles

    resultss = map (puzzle_07_extended_all_results_on_operands ops) operandss
    successfuls = map fst . filter (\(r,result) -> any (==r) result) $ zip rs resultss

    result = foldl' (+) 0 successfuls

puzzle_07_extended_all_results_on_operands :: [Int->Int->Int] -> [Int] -> [Int]
puzzle_07_extended_all_results_on_operands ops operands =
    result
  where
    (v:vs) = operands
    fn y = \x -> nubOrd $ map (\op -> x `op` y) ops
    fns = map fn vs
    master_fn = foldr1 (\acc f -> acc >=> f) fns

    -- note that no actual work on computing any results has occurred
    -- at any point.  We've just build a function that takes the first parameter.    
    
    result = master_fn v
    
    -- Even more interestingly, because of lazy evaluation, what
    -- we have produced is a list that can be expanded as needed.
    -- 'result' in C# or Rust would be an iterator owning all its own
    -- values for 'unfolding' into the singly linked list of results.



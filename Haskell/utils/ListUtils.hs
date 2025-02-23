module ListUtils
  (
    find_subsequence
    ,find_first_of_subsequences
    ,substitute_first_subsequence
    ,substitute_subsequence_at
    ,remove_nth
  ) where

import Data.List
import Data.List.Utils
import Data.List.Extra
import Data.Maybe


find_subsequence :: Eq a => [a] -> [a] -> Maybe Int 
find_subsequence sub str = findIndex (isPrefixOf sub) (tails str)

find_first_of_subsequences :: Eq a => [[a]] -> [a] -> Maybe (Int,Int) 
find_first_of_subsequences subs str = headDef Nothing . map Just . headDef [] . dropWhile null . map subs_in_tail . zip [0..] $ (tails str)
    where
        subs_in_tail (i,t) = zip (repeat i) . map fst . filter (\(_,sub) -> isPrefixOf sub t) . zip [0..] $ subs


substitute_first_subsequence :: Eq a => [a] -> [a] -> [a] -> Maybe [a]
substitute_first_subsequence old new str = result
    where
        (before,notbefore) = spanList (not . isPrefixOf old) str
        after = drop (length old) notbefore
        new_string = before ++ new ++ after
        result = if null notbefore then Nothing else Just new_string

substitute_subsequence_at :: Eq a => [a] -> Int -> [a] -> [a] -> Maybe [a]
substitute_subsequence_at old i new str = result
    where
        (before,notbefore) = splitAt i str
        after = drop (length old) notbefore
        new_string = before ++ new ++ after
        result = if (not . isSuffixOf old $ notbefore) then Nothing else Just new_string

remove_nth :: Int -> [a] -> [a]
remove_nth n xs = 
    as ++ bs
  where
    (as,(_:bs)) = splitAt n xs

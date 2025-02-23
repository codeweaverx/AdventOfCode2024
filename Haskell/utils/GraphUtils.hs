module GraphUtils(
    TopoMark
    ,topological_sort
    ,graphutils_edge_map_from_edges
  ) where

import Control.Monad
import qualified Data.Map as M
import Data.List


graphutils_edge_map_from_edges :: Ord a => [(a,a)] -> M.Map a [a]
graphutils_edge_map_from_edges = foldl' (\acc (k,v) -> M.insertWith (++) k [v] acc) M.empty

 


-- Topological Sorting
-- Tarjan 1976

{-
L ← Empty list that will contain the sorted nodes

-- Haskell: topological_sort
while exists nodes without a permanent mark do
    select an unmarked node n
    visit(n)

function visit(node n)
-- H
    if n has a permanent mark then
        return
    if n has a temporary mark then
        stop   (graph has at least one cycle)

    mark n with a temporary mark

    for each node m with an edge from n to m do
        visit(m)

    mark n with a permanent mark
    add n to head of L
-}

data TopoMark = TopoMarkNone | TopoMarkTemporary | TopoMarkPermanent deriving (Read,Show)

tt_edge_list = [(0,[1]), (1,[3,2]), (3,[4]), (4,[2,5]), (2,[6])]
tt_edges = M.fromList tt_edge_list
tt_node_list = [0,1,2,3,4,5,6]
tt_marked_nodes = M.fromList . map (\node -> (node,TopoMarkNone)) $ tt_node_list
-- topological_visit tt_edges 0 tt_marked_nodes

topological_visit :: Ord a => M.Map a [a] -> a -> M.Map a TopoMark -> Maybe ([a], M.Map a TopoMark)
topological_visit edges x marked_nodes =
    M.lookup x marked_nodes >>= handle_mark
  where
    marked_nodes_with_temp_x = M.insert x TopoMarkTemporary marked_nodes
    next_nodes = M.findWithDefault [] x edges

    handle_mark TopoMarkPermanent = Just ([],marked_nodes)
    handle_mark TopoMarkTemporary = Nothing
    handle_mark TopoMarkNone = 
      foldM (\(xs', marked_nodes') x' -> topological_visit edges x' marked_nodes' >>= fuse_visit_with_sibling_visits xs') ([],marked_nodes_with_temp_x) next_nodes 
        >>= finalize_result

    fuse_visit_with_sibling_visits xs' (xs_next, marked_nodes_next) = Just (xs_next ++ xs',marked_nodes_next)
    finalize_result (xs', marked_nodes') = Just (x:xs', M.insert x TopoMarkPermanent marked_nodes')



-- topological_sort tt_node_list tt_edge_list

topological_sort :: Ord a => [a] -> M.Map a [a] -> Maybe [a]
topological_sort node_list edges =
    possiblySorted
  where
    marked_nodes = M.fromList . map (\node -> (node,TopoMarkNone)) $ node_list

    possiblySorted = 
      foldM (\(xs', marked_nodes') x' -> topological_visit edges x' marked_nodes' >>= fuse_visit_with_sibling_visits xs') ([],marked_nodes) node_list 
        >>= finalize_result

    fuse_visit_with_sibling_visits xs' (xs_next, marked_nodes_next) = Just (xs_next ++ xs',marked_nodes_next)
    finalize_result (xs', _) = Just xs'

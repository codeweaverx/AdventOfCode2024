use std::hash::Hash;
pub use std::collections::HashMap;
pub use std::collections::HashSet;
use std::cmp::Eq;
use std::fmt::Debug;

//use crate::utils::container_utils;


#[derive(Debug)]
#[derive(Copy)]
#[derive(Clone)]
enum TopoMark {
  None
  ,Temporary
  ,Permanent
}

type Neighbours<K> = HashMap<K,Vec<K>>;
type Marks<K> = HashMap<K,TopoMark>;
//type KeyPairs<K> = Vec<(K,K)>;

pub fn edge_map_from_edges<'a,K>(edge_list : impl IntoIterator<Item = &'a(K,K)>) -> Neighbours<K>
  where K : 'a + Eq + Hash + Sized + Copy
{
  edge_map_from_edge_iter(edge_list.into_iter())
}



fn edge_map_from_edge_iter<'a,K>(edge_list : impl Iterator<Item = &'a(K,K)>) -> Neighbours<K>
  where K : 'a + Eq + Hash + Sized + Copy
{
  //let mut edges : Neighbours<K> = Neighbours::new();
  let mut edges = Neighbours::<K>::new();
  for (key,value) in edge_list
  {
    if let Some(neighbours) = edges.get_mut(&key) {
      neighbours.push(*value);
    } 
    else {
      let neighbours = vec![*value];
      edges.insert(*key,neighbours); 
    }
  }
 
  edges
}


pub fn node_list_from_edges<'a,K>(edge_list : impl IntoIterator<Item = &'a(K,K)>) -> Vec<K>
  where K : 'a + Eq + Hash + Sized + Copy
{
  node_list_from_edge_iter(edge_list.into_iter())
}


fn node_list_from_edge_iter<'a,K>(edge_list : impl Iterator<Item = &'a(K,K)>) -> Vec<K>
  where K : 'a + Eq + Hash + Sized + Copy
{
  let mut node_set : HashSet<K> = HashSet::new();
  for (key,value) in edge_list
  {
    node_set.insert(*key);
    node_set.insert(*value);
  }
 
  let nodes : Vec<K> = node_set.into_iter().collect();
  //let mut nodes : Vec<K> = node_set.into_iter().collect();
  //nodes.sort();

  nodes
}


/*

tt_edge_list = [(0,[1]), (1,[3,2]), (3,[4]), (4,[2,5]), (2,[6])]
tt_edges = M.fromList tt_edge_list
tt_node_list = [0,1,2,3,4,5,6]
tt_marked_nodes = M.fromList . map (\node -> (node,TopoMarkNone)) $ tt_node_list
-- topological_visit tt_edges 0 tt_marked_nodes



-- Topological Sorting
-- Tarjan 1976

L ← Empty list that will contain the sorted nodes

while exists nodes without a permanent mark do
    select an unmarked node n
    visit(n)

function visit(node n)
    if n has a permanent mark then
        return
    if n has a temporary mark then
        stop   (graph has at least one cycle)

    mark n with a temporary mark

    for each node m with an edge from n to m do
        visit(m)

    mark n with a permanent mark
    add n to head of L
*/

/*
fn topological_visit<'a,K>(edges : Neighbours<K>, x : K, marked_nodes : &mut Marks<K>, result : &mut Vec<K>) -> Option<&'a mut Vec<K>>
  where K : Eq, K : Hash, K : Sized, K : Copy
*/

// fn topological_visit<K>(edges : &Neighbours<K>, x : K, mut marked_nodes : &mut Marks<K>) -> Option<Vec<K>>
//   where K : Eq, K : Hash, K : Sized, K : Copy, K : Debug
// {
//   //println!("Processing: {x:?}");

//   let mark = marked_nodes.get(&x).copied().unwrap_or(TopoMark::None);
//   //println!("mark for {x:?} is {mark:?}");
//   match mark
//   {
//     TopoMark::Permanent => {return Some(Vec::new())}
//     ,TopoMark::Temporary => {/*println!("found cycle");*/ return None;} 
//     ,TopoMark::None => ()
//   }

//   marked_nodes.insert(x,TopoMark::Temporary);

//   let no_neighbours = Vec::new();
//   let next_nodes = edges.get(&x).unwrap_or(&no_neighbours);

//   let rss : Vec<Option<Vec<K>>> = 
//     next_nodes.into_iter()
//     .map(|x_| {let visit_chain = topological_visit(edges,*x_,&mut marked_nodes) ; visit_chain})
//     .take_while(|possible_rs| possible_rs.is_some())
//     .collect();

//   if rss.len() != next_nodes.len()
//   {
//     //println!("found deeper cycle {rss:?} {next_nodes:?}");
//     return None;
//   }

//   let rs : Vec<K> = vec!(x).into_iter().chain(rss.into_iter().map(|opt_rs| opt_rs.unwrap()).flatten()).collect();

//   marked_nodes.insert(x,TopoMark::Permanent);

//   //println!("Successful: {x:?} -> {rs:?}");
//   Some(rs)
// }



// pub fn topological_visit<K>(edges : &Neighbours<K>, x : K, mut marked_nodes : &mut Marks<K>) -> Option<Vec<K>>
//   where K : Eq, K : Hash, K : Sized, K : Copy, K : Debug
// {
//   //println!("Processing: {x:?}");

//   let mark = marked_nodes.get(&x).copied().unwrap_or(TopoMark::None);
//   //println!("mark for {x:?} is {mark:?}");
//   match mark
//   {
//     TopoMark::Permanent => {return Some(Vec::new())}
//     ,TopoMark::Temporary => {/*println!("found cycle");*/ return None;} 
//     ,TopoMark::None => ()
//   }

//   marked_nodes.insert(x,TopoMark::Temporary);

//   let no_neighbours = Vec::new();
//   let next_nodes = edges.get(&x).unwrap_or(&no_neighbours);

//   let possible_rs : Option<Vec<K>> = 
//     next_nodes.into_iter()
//     .try_fold(
//       vec![x]
//       ,|acc, x_| {
//         let visit_chain = topological_visit(edges,*x_,&mut marked_nodes) ; Some(acc.into_iter().chain(visit_chain?.into_iter()).collect())
//        }); 

//   marked_nodes.insert(x,TopoMark::Permanent);

//   // if let Some(rs) = possible_rs
//   // {
//   //   //println!("Successful: {x:?} -> {rs2:?}");
//   //   Some(rs)
//   // }
//   // else
//   // {
//   //   println!("found deeper cycle {possible_rs:?} {next_nodes:?}");
//   //   None
//   // }

//   possible_rs

// }




// trait TVI_I<Q>: Iterator<Item = Q> {}
// impl<Q,T:Iterator<Item = Q>> TVI_I<Q> for T {}


// fn topological_visit_stream<'a,K>(edges : &Neighbours<K>, x : K, mut marked_nodes : &mut Marks<K>) -> Option<Box<dyn TVI_I<K> + 'a>>
//   where K : 'a + Eq + Hash + Sized + Copy + Debug
// {
//   let mark = marked_nodes.get(&x).copied().unwrap_or(TopoMark::None);

//   match mark
//   {
//     TopoMark::Permanent => {return Some(Box::new(Vec::new().into_iter()));}
//     ,TopoMark::Temporary => {println!("found cycle"); return None;} 
//     ,TopoMark::None => ()
//   }

//   marked_nodes.insert(x,TopoMark::Temporary);

//   let no_neighbours = Vec::new();
//   let next_nodes = edges.get(&x).unwrap_or(&no_neighbours);

//   let possible_rs : Option<Box<dyn TVI_I<K>>> = 
//     next_nodes.into_iter()
//     .try_fold(
//       Box::new(Vec::new().into_iter()) as Box<dyn TVI_I<K>>
//       ,|acc, x_| {
//         let visit_chain = topological_visit_stream(edges,*x_,&mut marked_nodes) ; Some(Box::new(visit_chain?.chain(acc)) as Box<dyn TVI_I<K>>)
//        })
//     .map(|iter| Box::new(vec![x].into_iter().chain(iter)) as Box<dyn TVI_I<K>>); 

//   marked_nodes.insert(x,TopoMark::Permanent);

//   possible_rs
// }

// //For debug purposes only... we use the stream directly in the full solution
// fn topological_visit<K>(edges : &Neighbours<K>, x : K, marked_nodes : &mut Marks<K>) -> Option<Vec<K>>
//   where K : Eq, K : Hash, K : Sized, K : Copy, K : Debug
// {
//   topological_visit_stream(edges,x,marked_nodes).map(|iter| iter.collect::<Vec<K>>())
// }


// pub fn topological_sort<K>(phony_node : K, node_list : &Vec<K>, edges : &Neighbours<K>) -> Option<Vec<K>>
//   where K : Eq, K : Hash, K : Sized, K : Copy, K : Debug
// {
//   let mut edges_with_false_root = edges.clone();

//   edges_with_false_root.insert(phony_node,node_list.clone());

//   let mut marked_nodes = Marks::new();

//   topological_visit_stream(&edges_with_false_root,phony_node,&mut marked_nodes).map(|b| b.skip(1).collect::<Vec<K>>())
// }





fn topological_visit<K>(edges : &Neighbours<K>, x : K, mut marked_nodes : &mut Marks<K>, ys : Vec<K>) -> Option<Vec<K>>
  where K : Eq + Hash + Sized + Copy + Debug
{
  let mark = marked_nodes.get(&x).copied().unwrap_or(TopoMark::None);

  match mark
  {
    TopoMark::Permanent => {return Some(ys);}
    ,TopoMark::Temporary => {/*println!("found cycle");*/ return None;} 
    ,TopoMark::None => ()
  }

  marked_nodes.insert(x,TopoMark::Temporary);

  let no_neighbours = Vec::new();
  let next_nodes = edges.get(&x).unwrap_or(&no_neighbours);

  let possible_ys = 
    next_nodes.into_iter()
    .try_fold(
      ys
      ,|acc, x_| {
        topological_visit(edges,*x_,&mut marked_nodes, acc)
       })
    .map(|mut ys_| {ys_.push(x); return ys_;}); 

  marked_nodes.insert(x,TopoMark::Permanent);

  possible_ys
}

pub fn topological_sort<K>(phony_node : K, node_list : &Vec<K>, edges : &Neighbours<K>) -> Option<Vec<K>>
  where K : Eq, K : Hash, K : Sized, K : Copy, K : Debug
{
  let mut edges_with_false_root = edges.clone();

  edges_with_false_root.insert(phony_node,node_list.clone());

  topological_visit(&edges_with_false_root,phony_node,&mut Marks::new(),Vec::new()).map(|mut ys_| {ys_.reverse(); return ys_.into_iter().skip(1).collect::<Vec<K>>();})
}


pub fn debug_main()
{
  //type K = i64;

  let single_edge = edge_map_from_edges(&vec![(0,1)]);
  println!("single_edge: {single_edge:?}");

  let tree_of_edges = edge_map_from_edges(&vec![(0,1),(0,2),(0,3),(1,4),(1,5),(2,6),(3,7),(3,8),(3,9)]);
  println!("tree_of_edges: {tree_of_edges:?}");

  //[(0,[1]), (1,[3,2]), (3,[4]), (4,[2,5]), (2,[6])]
  let test_dag_edge_list = vec![(0,1), (1,3), (1,2), (3,4), (4,2), (4,5), (2,6)];
  let test_dag_edges = edge_map_from_edges(&test_dag_edge_list);
  let test_dag_nodes = node_list_from_edges(&test_dag_edge_list);

  {
    println!("test_dag_edges: {test_dag_edges:?}");
    //let mut marked_nodes = Marks::new();

    if let Some(result) = topological_visit(&test_dag_edges,0,&mut Marks::new(),Vec::new())
    {
      println!("topological_visit(test_dag_edges...): {result:?}");
    }
    else
    {
      println!("topological_visit(test_dag_edges...): (None)");
    }
  }

  {
    println!("test_dag_nodes: {test_dag_nodes:?}");
    println!("test_dag_edges: {test_dag_edges:?}");
    if let Some(result) = topological_sort(-1,&test_dag_nodes,&test_dag_edges)
    {
      println!("topological_sort(-1,test_dag_nodes,test_dag_edges): {result:?}");
    }
    else
    {
      println!("topological_sort(-1,test_dag_nodes,test_dag_edges): (None)");
    }
  }
}


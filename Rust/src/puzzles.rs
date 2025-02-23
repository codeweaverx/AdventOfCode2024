use crate::utils::graph_utils;
//use crate::utils::geometry_utils;
use crate::utils::geometry_utils::V2;
use std::iter;

pub use std::collections::HashMap;
pub use std::collections::HashSet;
//use std::hash::Hash;
//use std::cmp::Eq;
//use std::fmt::Debug;


pub fn puzzle_05_part1(input_ordering_pairs : &Vec<(i64,i64)>, input_update_sequences : &Vec<Vec<i64>>) -> i64
{
  //println!("input_ordering_pairs: {input_ordering_pairs:?}");
  //println!("input_update_sequences: {input_update_sequences:?}");
  let maybe_middle_pages : i64 = 
    input_update_sequences.into_iter()
    .map(|s| puzzle_05_part1_solve_one(input_ordering_pairs,s))
    .filter(|possible_page| possible_page.is_some())
    .map(|possible_page| possible_page.unwrap())
    .sum();
  return maybe_middle_pages;
}


fn puzzle_05_part1_solve_one(ordering_pairs : &Vec<(i64,i64)>, update_sequence : &Vec<i64>) -> Option<i64>
{
  //println!("ordering_pairs: {ordering_pairs:?}");
  //println!("update_sequence: {update_sequence:?}");
  let sequence_set = HashSet::<i64>::from_iter(update_sequence.into_iter().cloned());
  
  let useful_pairs = ordering_pairs.into_iter().filter(|(from,to)| sequence_set.contains(from) && sequence_set.contains(to));
  let pairs_from_update_sequences : Vec<(i64,i64)> = update_sequence.into_iter().cloned().zip(update_sequence.into_iter().skip(1).cloned()).collect();

  let test_pairs = useful_pairs.chain(&pairs_from_update_sequences);
  let edges : HashMap<i64,Vec<i64>> = graph_utils::edge_map_from_edges(test_pairs);

  let can_sort = graph_utils::topological_sort(-1, &update_sequence, &edges).is_some();

  let maybe_middle_page = 
    if can_sort
    {
      Some(update_sequence.into_iter().skip(update_sequence.len() / 2).next().map(|possible| *possible).unwrap())
    }
    else
    {
      None
    };

  maybe_middle_page
}


pub fn puzzle_05_part2(ordering_pairs : &Vec<(i64,i64)>, update_sequences : &Vec<Vec<i64>>) -> i64
{
  //println!("input_ordering_pairs: {input_ordering_pairs:?}");
  //println!("input_update_sequences: {input_update_sequences:?}");
  let maybe_solveables = update_sequences.into_iter().zip(update_sequences.into_iter().map(|s| puzzle_05_part1_solve_one(ordering_pairs, s)));
  let unsolveables = maybe_solveables.filter(|(_,possible_s)| possible_s.is_none()).map(|(s,_)| s);
  let made_solveables = unsolveables.map(|s| puzzle_05_part2_solve_one(ordering_pairs,s));

  let sum_middle_pages = 
    made_solveables.filter(|possible_s| possible_s.is_some()).map(|possible_s| possible_s.unwrap()).sum();

  sum_middle_pages
}

fn puzzle_05_part2_solve_one(ordering_pairs : &Vec<(i64,i64)>, update_sequence : &Vec<i64>) -> Option<i64>
{
  let sequence_set = HashSet::<i64>::from_iter(update_sequence.into_iter().cloned());
  let useful_pairs = ordering_pairs.into_iter().filter(|(from,to)| sequence_set.contains(from) && sequence_set.contains(to));
  let edges : HashMap<i64,Vec<i64>> = graph_utils::edge_map_from_edges(useful_pairs);
  let possible_xs = graph_utils::topological_sort(-1,update_sequence,&edges);
  
  let maybe_middle_page = possible_xs.map(|xs| {let n = xs.len();xs.into_iter().skip(n/2).next().unwrap()});
  
  maybe_middle_page
}


#[derive(Debug)]
#[derive(Copy)]
#[derive(Clone)]
enum Puzzle06CellType {
  Nothing
  ,Blockage
  ,Termination
}

type Puzzle06Grid = Vec<Vec<Puzzle06CellType>>;

type Puzzle06Pos = V2<i64>;
type Puzzle06Vel = V2<i64>;

pub fn puzzle_06_part1(raw_grid : &Vec<&str>) -> i64
{
  let (grid,guard_pos,guard_vel) = puzzle_06_part1_build_bounded_grid(raw_grid);

  let adjusted_guard_pos = guard_pos + Puzzle06Vel{x:1, y:1};

  puzzle_06_part1_go(&grid, adjusted_guard_pos, guard_vel)
}


fn puzzle_06_part1_go(grid : &Puzzle06Grid, guard_pos : Puzzle06Pos, guard_vel : Puzzle06Vel) -> i64
{
  let guard_positions = 
    puzzle_06_part1_generate_guard_positions(&grid, guard_pos, guard_vel)
    .map(|(p,_)| p);

  let count_of_unique_guard_positions =
    guard_positions
    .fold(HashSet::new(),|mut h,e| {h.insert(e); h})
    .len();

  count_of_unique_guard_positions as i64
}


fn puzzle_06_part1_generate_guard_positions(grid : &Puzzle06Grid, guard_pos : Puzzle06Pos, guard_vel : Puzzle06Vel) -> impl Iterator<Item = (Puzzle06Pos,Puzzle06Vel)> + '_
{
  //successors is basically unfoldr, except the seed has to match the output.
  let guard_positions = 
    iter::successors(Some((guard_pos,guard_vel)),|&(pos,vel)| puzzle_06_part1_guard_step(grid,pos,vel))
    ;//.inspect(|pv| println!("{pv:?}"));

  guard_positions
}


fn puzzle_06_part1_build_bounded_grid(raw_grid : &Vec<&str>) -> (Puzzle06Grid,Puzzle06Pos,Puzzle06Vel)
{
  let w = raw_grid[0].len();

  let mut guard_vel = Puzzle06Vel{x:0,y:0};
  let mut guard_pos = Puzzle06Pos{x:0,y:0};
  let mut map_cell =  //required to be mut because it captures guard_vel and guard_pos by mutable reference.
    |pos,c|
      match c
      {
        '.' => Puzzle06CellType::Nothing
        ,'#' => Puzzle06CellType::Blockage
        ,'X' => Puzzle06CellType::Termination
        ,'^' => {guard_vel=Puzzle06Vel{x:0,y:-1}; guard_pos=pos; Puzzle06CellType::Nothing}
        ,'>' => {guard_vel=Puzzle06Vel{x:1,y:0}; guard_pos=pos; Puzzle06CellType::Nothing}
        ,'v' => {guard_vel=Puzzle06Vel{x:0,y:1}; guard_pos=pos; Puzzle06CellType::Nothing}
        ,'<' => {guard_vel=Puzzle06Vel{x:-1,y:0}; guard_pos=pos; Puzzle06CellType::Nothing}
        ,_ => panic!("Unhandled cell type")
      };

  let grid : Puzzle06Grid = 
    iter::once(iter::repeat_n(Puzzle06CellType::Termination,w).collect::<Vec<Puzzle06CellType>>())
    .chain(
      raw_grid
      .into_iter()
      .enumerate()
      .map(|(j,row)| 
        iter::once(Puzzle06CellType::Termination)
        .chain(
          row
          .chars()
          .enumerate()
          .map(|(i,c)| map_cell(V2{x:i as i64,y:j as i64},c)))
        .chain(iter::once(Puzzle06CellType::Termination)).collect()))
    .chain(
      iter::once(iter::repeat_n(Puzzle06CellType::Termination,w).collect::<Vec<Puzzle06CellType>>()))
    .collect();

    (grid,guard_pos,guard_vel)
}


fn puzzle_06_part1_guard_step(grid: &Puzzle06Grid, pos:Puzzle06Pos, mut vel:Puzzle06Vel) -> Option<(Puzzle06Pos,Puzzle06Vel)>
{
  for _ in 0..4
  {
    let pos2 = pos+vel;
    let vel2 = Puzzle06Vel{x : -vel.y, y : vel.x}; //positive y down, rotate clockwise 90 degrees

    match grid[pos2.y as usize][pos2.x as usize]
    {
      Puzzle06CellType::Nothing      => {return Some((pos2,vel));}
      ,Puzzle06CellType::Blockage    => ()
      ,Puzzle06CellType::Termination => {return None;}
      //,_ => panic!("Unhangled cell type.")
    }

    vel = vel2;
  }

  None
}




pub fn puzzle_06_part2(raw_grid : &Vec<&str>) -> i64
{
  let (grid,guard_pos,guard_vel) = puzzle_06_part1_build_bounded_grid(raw_grid);

  let adjusted_guard_pos = guard_pos + Puzzle06Vel{x:1, y:1};

  puzzle_06_part2_go(&grid, adjusted_guard_pos, guard_vel)
}




fn puzzle_06_part2_go(grid : &Puzzle06Grid, guard_pos : Puzzle06Pos, guard_vel : Puzzle06Vel) -> i64
{
  let guard_positions = 
    puzzle_06_part1_generate_guard_positions(&grid, guard_pos, guard_vel)
    .map(|(p,_)| p);


  //if we're going to change the guard path by adding an obstacle
  //then by definition the only places we need to examine are
  //those positions that the guard visits in the path that
  //properly escapes.

  let list_of_known_escaping_guard_positions = 
    guard_positions
      .fold(HashSet::new(),|mut h,e| {h.insert(e); h})
      .into_iter();

  let mut grid_copy = grid.clone();

  //Use that known visited list of positions
  let num_cycle_creators = list_of_known_escaping_guard_positions
    .map(|pos| puzzle_06_part2_find_cycle(pos,&mut grid_copy,guard_pos,guard_vel))
    .map(|possible_cycle| possible_cycle.is_some())
    .filter(|&b| b)
    .count();

  num_cycle_creators as i64
}



type Puzzle06Visitation = HashMap<Puzzle06Pos,Vec<Puzzle06Vel>>;




fn puzzle_06_part2_find_cycle(test_pos : Puzzle06Pos, old_grid : &Puzzle06Grid, guard_pos : Puzzle06Pos, guard_vel : Puzzle06Vel) -> Option<(Puzzle06Pos,Puzzle06Vel)>
{
  let mut grid = old_grid.clone();
  grid[test_pos.y as usize][test_pos.x as usize] = Puzzle06CellType::Blockage;

  let mut guard_positions = 
    puzzle_06_part1_generate_guard_positions(&grid, guard_pos, guard_vel);

  let mut possible_cycle : Option<(Puzzle06Pos,Puzzle06Vel)> = None;
  let mut visited : Puzzle06Visitation = Puzzle06Visitation::new();
  while possible_cycle.is_none(){
    if let Some((p,v)) = guard_positions.next()
    {
      if let Some(vels) = visited.get_mut(&p)
      {
        if vels.contains(&v)
        {
          possible_cycle = Some((p,v));
        }
        else
        {
          vels.push(v);
        }
      }
      else
      {
        visited.insert(p,vec![v]);
      }
    }
    else
    {
      break;
    }
  }

  possible_cycle
}






// fn puzzle_06_part2_find_cycle(test_pos : Puzzle06Pos, grid : &mut Puzzle06Grid, guard_pos : Puzzle06Pos, guard_vel : Puzzle06Vel) -> Option<(Puzzle06Pos,Puzzle06Vel)>
// {
//   let (x,y) = (test_pos.x,test_pos.y);

// //  let mut grid = old_grid.clone();
//   let mut ref_cell = &mut grid[test_pos.y as usize][test_pos.x as usize];
//   let old_cell = *ref_cell;
//   *ref_cell = Puzzle06CellType::Blockage;

//   //println!("({x},{y}): old cell = {old_cell:?} *ref_cell = {ref_cell:?}");

//   ref_cell = &mut Puzzle06CellType::Blockage;

//   let mut possible_cycle : Option<(Puzzle06Pos,Puzzle06Vel)> = None;

//   {
//     let mut guard_positions = 
//       puzzle_06_part1_generate_guard_positions(&grid, guard_pos, guard_vel);

//     let mut visited : Puzzle06Visitation = Puzzle06Visitation::new();

//     while possible_cycle.is_none(){
//       if let Some((p,v)) = guard_positions.next()
//       {
//         if let Some(vels) = visited.get_mut(&p)
//         {
//           if vels.contains(&v)
//           {
//             possible_cycle = Some((p,v));
//           }
//           else
//           {
//             vels.push(v);
//           }
//         }
//         else
//         {
//           visited.insert(p,vec![v]);
//         }
//       }
//       else
//       {
//         break;
//       }
//     }
//   }

//   // if possible_cycle.is_none()
//   // {
//   //   println!("({x},{y}): Escaped loop with no cycle");
//   // }
//   // else
//   // {
//   //   println!("({x},{y}): Escaped loop with cycle");
//   // }
  
//   ref_cell = &mut grid[test_pos.y as usize][test_pos.x as usize];
//   *ref_cell = old_cell;

//   possible_cycle
// }






// ---
// Beautiful failure -- ref_cell borrows the entire grid as
// mutable, because borrowing a part borrows the whole by
// default.  But we use it before and after a 'search' is done
// and Rust considers that mutable borrow to be 'live' over that
// call.  That's not allowed.
//

// fn puzzle_06_part2_find_cycle(test_pos : Puzzle06Pos, grid : &mut Puzzle06Grid, guard_pos : Puzzle06Pos, guard_vel : Puzzle06Vel) -> Option<(Puzzle06Pos,Puzzle06Vel)>
// {
// //  let mut grid = old_grid.clone();
//   let ref_cell = &mut grid[test_pos.y as usize][test_pos.x as usize];
//   let old_cell = *ref_cell;
//   *ref_cell = Puzzle06CellType::Blockage;

//   //println!("old cell = {old_cell:?} *ref_cell = {ref_cell:?}");

//   let mut guard_positions = 
//     puzzle_06_part1_generate_guard_positions(&grid, guard_pos, guard_vel);

//   let mut possible_cycle : Option<(Puzzle06Pos,Puzzle06Vel)> = None;
//   let mut visited : Puzzle06Visitation = Puzzle06Visitation::new();

//   while possible_cycle.is_none(){
//     if let Some((p,v)) = guard_positions.next()
//     {
//       if let Some(vels) = visited.get_mut(&p)
//       {
//         if vels.contains(&v)
//         {
//           possible_cycle = Some((p,v));
//           break;
//         }
//         else
//         {
//           vels.push(v);
//         }
//       }
//       else
//       {
//         visited.insert(p,vec![v]);
//       }
//     }
//     else
//     {
//       possible_cycle = None; //guard list ended, so we escaped.  No cycle.
//       break;
//     }
//   }

//   *ref_cell = old_cell;

//   possible_cycle
// }
















#include <cassert>
#include <vector>
#include <map>
#include <set>
#include <tuple>
//#include <pair>
#include <cctype>
#include <regex>
#include <algorithm>
#include <functional>
#include <numeric>
#include <sstream>
#include <string_view>
#include <ranges>
#include <cmath>
#include <iterator>
#include <span>

#include "SimpleLinkedList.h"

#include "Puzzles.h"
#include "geometry_utils.h"
#include "iostreamext.h"

namespace puzzle_01
{
  //Values come in as a 'vector of tuples of int', basically a list of pairs of values,
  //literally the line by line, but parsed, version of the input data
  int puzzle_01_part1(const std::vector<std::tuple<int,int>> &arbitrary_pairs)
  {
    //Mimics Haskell's unzip operation.  Should have used C++23's fold_left
    //but it seemed too much like code golf.  So C++11's for_each it is.
    //We could also use C++20's range based for_each so we don't have to use
    //begin and end iterators, but we can 'mix it up a bit'.
    using TupleOfLists = std::tuple<std::vector<int>,std::vector<int>>;
    TupleOfLists unzipped_as_tuple{};
    std::ranges::for_each(arbitrary_pairs.begin(), arbitrary_pairs.end(), 
      [&unzipped_as_tuple](const auto& t) {
          std::get<0>(unzipped_as_tuple).push_back(std::get<0>(t));
          std::get<1>(unzipped_as_tuple).push_back(std::get<1>(t));
        });

    auto [l0,l1] = unzipped_as_tuple;

    std::ranges::sort(l0);
    std::ranges::sort(l1);

    //Okay, now do a C++23 fold_left where I don't have to explain
    //mutating jank.
    const auto distance = 
      std::ranges::fold_left(
        std::ranges::views::zip(l0,l1) //zip | transform could be done as a C++23 zip_transform
        | std::ranges::views::transform(
          [](const auto& t) {
              const int x = std::get<0>(t);
              const int y = std::get<1>(t);
              return std::abs(x-y);
            })
        ,0,
          [](const int acc,const int x){
            return acc+x;
          });

    return distance; 
  }

  //Values come in as a 'vector of tuples of int', basically a list of pairs of values,
  //literally the line by line, but parsed, version of the input data
  int puzzle_01_part2(const std::vector<std::tuple<int,int>> &arbitrary_pairs)
  {
    //Okay, let's use a left fold here instead.  The lists will come out
    //backwards, but we don't need to re-reverse them -- it doesn't matter
    //for this puzzle.
    //Also note that although we're getting a vector each call to that
    //lambda, modifying it, and returning it, we're receiving it as an
    //rvalue reference, meaning its originating vector in the caller, and
    //(almost certainly) all the way back to the last time it was returned,
    //is being 'moved into' the function (ie, not copied), and also
    //moved out (through standard return mechanisms).  No intermediate
    //vector copies are made.  This is not quadratic behaviour, it's
    //linear because of move semantics.
    using TupleOfLists = std::tuple<std::vector<int>,std::vector<int>>;
    const auto unzipped_as_tuple =
      std::ranges::fold_left(arbitrary_pairs, TupleOfLists{}, 
        [](auto&& t_of_ls, const auto& t) {
            std::get<0>(t_of_ls).push_back(std::get<0>(t));
            std::get<1>(t_of_ls).push_back(std::get<1>(t));
            return t_of_ls;
          });

    const auto& [l0,l1] = unzipped_as_tuple;

    //Let's leave this one as a for_each, but use the ranges version.
    //Its effectively one line longer than a left fold version,
    //but just for the variety.
    //It also leaves the histogram modifyable which is sad, which
    //the std::left_fold or std::accumulate version would address.
    std::map<int,int> histogram{};
    std::ranges::for_each(l1, 
      [&histogram](const int i){
        if (const auto [iter,success] = histogram.try_emplace(i,1); !success)
        {
          iter->second += 1;
        }

      });


    const auto distance = 
      std::ranges::fold_left(l0,0,
          [&histogram](const int acc,const int i){
            const auto iter = histogram.find(i);
            return acc + ((iter==std::end(histogram)) ? 0 : (iter->second * i));
          });

    return distance; 
  }
 


  int puzzle_01_part1_istream_read(std::string&& input_string)
  {
    auto in = std::istringstream(std::move(input_string)); //own the string
    auto in_iter = std::istream_iterator<int>(in);
    auto in_iter_end = std::istream_iterator<int>();

    auto input = std::vector<std::tuple<int,int>>{};
    //turn it into my canonical std::vector<std::tuple> format
    //Assumes even number of ints.
    for(auto i = in_iter; i != in_iter_end; ++i)
    {
      const auto x = *i;
      ++i;
      const auto y = *i;
      input.push_back(std::make_tuple(x,y));
    }

    input_string = std::move(in.str()); //give it back

    return puzzle_01_part1(input);
  }
  
}


namespace puzzle_02
{
  bool puzzle_02_part1_one_line(const std::vector<int>& xs)
  {
    const auto [x0,y0] = std::make_tuple(*std::begin(xs),*(std::begin(xs)+1));
    auto cmp = (x0>y0)
          ? [](const int x, const int y){return x>y;}
          : [](const int x, const int y){return x<y;};

    for(auto ix = std::begin(xs), jx = ix + 1; jx != std::end(xs); ++ix, ++jx)
    {
      if (abs(*ix - *jx)>3)
      {
        return false;
      }
      if (!cmp(*ix,*jx))
      {
        return false;
      }
      
    }

    return true;
  }

  int puzzle_02_part1(const std::vector<std::vector<int>> &xss)
  {
    int valid_count = 0;
    for(auto ixs = std::begin(xss); ixs != std::end(xss); ++ixs)
    {
      const auto is_valid = puzzle_02_part1_one_line(*ixs);
      if (is_valid)
      {
        ++valid_count;
      }
    }
    return valid_count;
  }



  bool puzzle_02_part2_one_line_without_ith(const std::vector<int>& xs, const std::vector<int>::const_iterator& i_skip)
  {
    auto j_prev = std::begin(xs);
    if (j_prev == i_skip)
    {
      ++j_prev;
    }

    bool ascent_established = false;
    bool ascending = true;

    // std::cout << "====" << std::endl;
    // std::cout << "xs == " << xs << " i_skip == " << i_skip - std::begin(xs) << std::endl;
    // std::cout << "====" << std::endl;
    for (auto jxs = std::next(j_prev); jxs != std::end(xs); ++jxs)
    {
      if (jxs == i_skip)
      {
        continue;
      }

      // std::cout << "jprev == " << *j_prev << " jxs == " << *jxs << std::endl;

      if (*jxs == *j_prev)
      {
        return false; //automatically a failure.
      }

      if (!ascent_established)
      {
        ascent_established = true;
        ascending = (*jxs > *j_prev);
      }

      if (abs(*jxs - *j_prev)>3 || ascending != (*jxs > *j_prev))
      {
        return false;
      }

      ++j_prev;
      if (j_prev == i_skip)
      {
        ++j_prev;
      }
    }
    return true;
  }

  bool puzzle_02_part2_one_line(const std::vector<int>& xs)
  {
    if (xs.size() < 2)
    {
      return true;
    }

    for (auto i = std::begin(xs); i!= std::end(xs); ++ i)
    {
      const auto success = puzzle_02_part2_one_line_without_ith(xs,i);
      if (success)
      {
        return true;
      }
    }
    return false;
  }

  int puzzle_02_part2(const std::vector<std::vector<int>> &xss)
  {
    int valid_count = 0;
    for(auto ixs = std::begin(xss); ixs != std::end(xss); ++ixs)
    {
      const auto is_valid = puzzle_02_part2_one_line(*ixs);
      if (is_valid)
      {
        ++valid_count;
      }
    }
    return valid_count;
  }


}

namespace puzzle_03
{
  using CI = std::string::const_iterator;
  using PossibleParseIntResultType = std::optional<std::tuple<CI,int>>;
  using ParseMulResultType = std::tuple<CI,int,int>;
  using PossibleParseMulResultType = std::optional<ParseMulResultType>;
  using ParseResultType = std::vector<std::tuple<int,int>>;

  PossibleParseIntResultType parseInt(CI i, const CI& end)
  {
    if (i == end || !std::isdigit(*i))
    {
      return PossibleParseIntResultType{};
    }

    int num = 0;
    while (i != end && std::isdigit(*i))
    {
      num = num*10 + (*i - '0');
      ++i;      
    }

    return PossibleParseIntResultType{std::make_tuple(i,num)};
  }

  PossibleParseMulResultType parseMul(CI i, const CI& end)
  {
    if (i == end || *i != 'm')
    {
      return PossibleParseMulResultType{};
    }
    ++i;

    if (i == end || *i!= 'u')
    {
      return PossibleParseMulResultType{};
    }
    ++i;

    if (i == end || *i != 'l')
    {
      return PossibleParseMulResultType{};
    }
    ++i;

    if (i == end || *i != '(')
    {
      return PossibleParseMulResultType{};
    }
    ++i;

    const auto possibleN1 = parseInt(i,end);
    if (!possibleN1.has_value())
    {
      return PossibleParseMulResultType{};
    }
    int n1 = std::get<1>(possibleN1.value());
    i = std::get<0>(possibleN1.value());


    if (i == end || *i != ',')
    {
      return PossibleParseMulResultType{};
    }
    ++i;    

    const auto possibleN2 = parseInt(i,end);
    if (!possibleN2.has_value())
    {
      return PossibleParseMulResultType{};
    }
    int n2 = std::get<1>(possibleN2.value());
    i = std::get<0>(possibleN2.value());


    if (i == end || *i != ')')
    {
      return PossibleParseMulResultType{};
    }
    ++i;

    return PossibleParseMulResultType{std::make_tuple(i,n1,n2)};
  }

  int parse(CI i, const CI& end)
  {
    CI debug_start_i = i;

    auto parseResult = ParseResultType{};

    while (i != end)
    {
      while (i != end && *i != 'm')
      {
        ++i;
      }
      if (i == end)
      {
        break;
      }

      const auto possibleParseMulResult = parseMul(i,end);
      if (!possibleParseMulResult.has_value())
      {
        ++i;
        continue;
      }

      const auto& v = possibleParseMulResult.value();
      parseResult.push_back(std::make_tuple(std::get<1>(v), std::get<2>(v)));
      i = std::get<0>(v);
    }


    const auto result = std::accumulate(parseResult.begin(),parseResult.end(),0
      ,[](const int acc, const std::tuple<int,int>& mul_pair){
        return acc + std::get<0>(mul_pair) * std::get<1>(mul_pair);
      });

    return result;
  }

  int puzzle_03_part1(const std::string& memory)
  {
    const auto result = parse(std::begin(memory),std::end(memory));

    return result;
  }
  
//----------------------------------------------------

  using ParseDoResultType = std::tuple<CI>;
  using PossibleParseDoResultType = std::optional<ParseDoResultType>;
  using ParseDontResultType = std::tuple<CI>;
  using PossibleParseDontResultType = std::optional<ParseDontResultType>;

  PossibleParseDoResultType parseDo(CI i, const CI& end)
  {
    if (i == end || *i != 'd')
    {
      return PossibleParseDoResultType{};
    }
    ++i;

    if (i == end || *i!= 'o')
    {
      return PossibleParseDoResultType{};
    }
    ++i;

    if (i == end || *i!= '(')
    {
      return PossibleParseDoResultType{};
    }
    ++i;

    if (i == end || *i!= ')')
    {
      return PossibleParseDoResultType{};
    }
    ++i;

    return PossibleParseDoResultType{std::make_tuple(i)};
  }

  PossibleParseDontResultType parseDont(CI i, const CI& end)
  {
    if (i == end || *i != 'd')
    {
      return PossibleParseDontResultType{};
    }
    ++i;

    if (i == end || *i!= 'o')
    {
      return PossibleParseDontResultType{};
    }
    ++i;

    if (i == end || *i!= 'n')
    {
      return PossibleParseDontResultType{};
    }
    ++i;

    if (i == end || *i!= '\'')
    {
      return PossibleParseDontResultType{};
    }
    ++i;

    if (i == end || *i!= 't')
    {
      return PossibleParseDontResultType{};
    }
    ++i;

    if (i == end || *i!= '(')
    {
      return PossibleParseDontResultType{};
    }
    ++i;

    if (i == end || *i!= ')')
    {
      return PossibleParseDontResultType{};
    }
    ++i;

    return PossibleParseDontResultType{std::make_tuple(i)};
  }

  int parse_part2(CI i, const CI& end)
  {
    CI debug_start_i = i;

    auto parseResult = ParseResultType{};
    auto accept_muls = true;

    while (i != end)
    {

      bool foundCommand = false;

      const auto possibleParseMulResult = parseMul(i,end);
      if (possibleParseMulResult.has_value())
      {
        const auto& v = possibleParseMulResult.value();
        if (accept_muls)
        {
          parseResult.push_back(std::make_tuple(std::get<1>(v), std::get<2>(v)));
        }
        i = std::get<0>(v);
        
        continue;
      }

      const auto possibleParseDoResult = parseDo(i,end);
      if (possibleParseDoResult.has_value())
      {
        const auto& v = possibleParseDoResult.value();
        accept_muls = true;
        i = std::get<0>(v);
        
        continue;
      }

      const auto possibleParseDontResult = parseDont(i,end);
      if (possibleParseDontResult.has_value())
      {
        const auto& v = possibleParseDontResult.value();
        accept_muls = false;
        i = std::get<0>(v);
        
        continue;
      }

      ++i;

    }


    const auto result = std::accumulate(parseResult.begin(),parseResult.end(),0
      ,[](const int acc, const std::tuple<int,int>& mul_pair){
        return acc + std::get<0>(mul_pair) * std::get<1>(mul_pair);
      });

    return result;
  }

  int puzzle_03_part2(const std::string& memory)
  {
    const auto result = parse_part2(std::begin(memory),std::end(memory));

    return result;
  }
}


namespace puzzle_04
{
  using Row = std::string;
  using Grid = std::vector<Row>;

  using Pos2 = std::tuple<std::size_t,std::size_t>;
  using Vec2 = std::tuple<std::ptrdiff_t,std::ptrdiff_t>;
  Pos2 operator+(const Pos2 pos, const Vec2 vec)
  {
    //All this nonsense to add a sized value to an unsigned value but leave it in the unsigned value's type
    const int i = std::get<0>(vec)>0 ? static_cast<std::string::size_type>(std::get<0>(pos)) + std::get<0>(vec) : std::get<0>(pos) - static_cast<std::string::size_type>(-std::get<0>(vec));
    const int j = std::get<1>(vec)>0 ? static_cast<std::string::size_type>(std::get<1>(pos)) + std::get<1>(vec) : std::get<1>(pos) - static_cast<std::string::size_type>(-std::get<1>(vec));
    return Pos2(i,j);
  }

  inline
  Pos2& operator+=(Pos2& pos, const Vec2 vec) {pos = pos + vec; return pos;}

  inline
  int part_04_is_in_bounds(const Grid& g,const Pos2 pos)
  {
    return
      static_cast<Grid::size_type>(std::get<1>(pos)) < g.size()
      && static_cast<Grid::size_type>(std::get<0>(pos)) < g[0].size();
  }


  int part_04_match_in_line(int acc,const Grid& g, std::string::const_iterator i_str, std::string::const_iterator i_str_end, const Pos2 pos, const Vec2 dir)
  {
    if (i_str == i_str_end)
    {
      return acc+1;
    }
    if (!part_04_is_in_bounds(g,pos))
    {
      return acc;
    }
    const char gc = g[std::get<1>(pos)][std::get<0>(pos)];
    if (gc != *i_str)
    {
      return acc;
    }
    return part_04_match_in_line(acc,g,std::next(i_str),i_str_end,pos+dir,dir);
  }

  int part_04_search_line(int acc,const Grid& g, const std::string& s, const Pos2 pos, const Vec2 dir)
  {
    if (!part_04_is_in_bounds(g,pos))
    {
      return acc;
    }
    
    //const int old_acc = acc;
    acc = part_04_match_in_line(acc,g,std::begin(s),std::end(s),pos,dir);
    // if (acc!=old_acc)
    // {
    //   std::cout << "===" << std::endl;
    //   std::cout << "Found match at " << std::get<0>(pos) << "," << std::get<1>(pos) << std::endl;      
    // }
    return part_04_search_line(acc,g,s,pos + dir,dir);
  }


  int part_04_search_rows(int acc,const Grid& g, const std::string& s, const std::size_t row)
  {
    const auto pos = Pos2(0,row);
    if (!part_04_is_in_bounds(g,pos))
    {
      return acc;
    }
    acc = part_04_search_line(acc,g,s,pos,Vec2(1,0));

    const auto reverse_pos = Pos2(g[0].size()-1,row);
    acc = part_04_search_line(acc,g,s,reverse_pos,Vec2(-1,0));

    return part_04_search_rows(acc,g,s,row+1);
  }

  int part_04_search_cols(int acc,const Grid& g, const std::string& s, const std::size_t col)
  {
    const auto pos = Pos2(col,0);
    if (!part_04_is_in_bounds(g,pos))
    {
      return acc;
    }
    acc = part_04_search_line(acc,g,s,pos,Vec2(0,1));

    const auto reverse_pos = Pos2(col,g.size()-1);
    acc = part_04_search_line(acc,g,s,reverse_pos,Vec2(0,-1));

    return part_04_search_cols(acc,g,s,col+1);
  }


  int part_04_search_diags_from_leftright(int acc,const Grid& g, const std::string& s, const std::size_t row)
  {
    if (row == 0 || row == g.size()-1) // to avoid counting the primary diagonals twice.
    {
      return part_04_search_diags_from_leftright(acc,g,s,row+1);
    }

    const auto lft_pos = Pos2(0,row);
    if (!part_04_is_in_bounds(g,lft_pos))
    {
      return acc;
    }
    acc = part_04_search_line(acc,g,s,lft_pos,Vec2(1,1));
    acc = part_04_search_line(acc,g,s,lft_pos,Vec2(1,-1));

    const auto rgt_pos = Pos2(g[0].size()-1,row);
    acc = part_04_search_line(acc,g,s,rgt_pos,Vec2(-1,1));
    acc = part_04_search_line(acc,g,s,rgt_pos,Vec2(-1,-1));

    return part_04_search_diags_from_leftright(acc,g,s,row+1);
  }

  int part_04_search_diags_from_topbottom(int acc,const Grid& g, const std::string& s, const std::size_t col)
  {
    const auto top_pos = Pos2(col,0);
    if (!part_04_is_in_bounds(g,top_pos))
    {
      return acc;
    }
    acc = part_04_search_line(acc,g,s,top_pos,Vec2(1,1));
    acc = part_04_search_line(acc,g,s,top_pos,Vec2(-1,1));

    const auto bot_pos = Pos2(col,g.size()-1);
    acc = part_04_search_line(acc,g,s,bot_pos,Vec2(1,-1));
    acc = part_04_search_line(acc,g,s,bot_pos,Vec2(-1,-1));

    return part_04_search_diags_from_topbottom(acc,g,s,col+1);
  }


  int puzzle_04_search_grid(const Grid& g, const std::string& s)
  {
    const auto n = g.size();

    int acc = 0;
    acc = part_04_search_rows(acc,g,s,0);
    acc = part_04_search_cols(acc,g,s,0);
    acc = part_04_search_diags_from_leftright(acc,g,s,0);
    acc = part_04_search_diags_from_topbottom(acc,g,s,0);
    return acc;
  }

  void DumpGrid(const Grid& g)
  {
    for (const auto &r : g)
    {
      for (const auto &c : r)
      {
        std::cout << c;
      }
      std::cout << std::endl;
    }
  }

  int puzzle_04_part1(const std::vector<std::string>& grid)
  {
    //Grid ll_grid{};

    // Test on this grid to make sure the search doesn't
    // break recursion limits.
    // const int n = 10000000;
    // for (int j = 0; j < n; ++j)
    // {
    //   Row row{};
    //   for (int i = 0; i < 1; ++i)
    //   {
    //     row.push_back('X');
    //   }
    //   ll_grid.push_back(std::move(row));
    // }

    return puzzle_04_search_grid(grid,"XMAS");
  }


  int puzzle_04_part2(const std::vector<std::string>& grid)
  {
    const auto cross_order = std::string("MMSS");

    int count = 0;

    for (std::size_t j = 1; j < grid.size()-1; ++j)
    {
      for (std::size_t i = 1; i < grid.size()-1; ++i)
      {
        bool found = false;
        for (int cross_offset = 0; cross_offset < 4 && !found; ++cross_offset)
        {
          if (grid[j][i] != 'A') {continue;}
          if (grid[j+1][i+1] != cross_order[(cross_offset)]) {continue;}
          if (grid[j+1][i-1] != cross_order[(cross_offset+1)%4]) {continue;}
          if (grid[j-1][i-1] != cross_order[(cross_offset+2)%4]) {continue;}
          if (grid[j-1][i+1] != cross_order[(cross_offset+3)%4]) {continue;}
          found = true;
        }
        if (found)
        {
          ++count;
        }
      }
    }

    return count;
  }

}



namespace puzzle_08
{
  using namespace std::ranges::views;
  using namespace geometry_utils;

  struct Tower
  {
    char id;
    Vec2<int> pos;
  };

  std::ostream& operator<<(std::ostream& out, const Tower& t)
  {
    return out << "Tower{ id=" << static_cast<int>(t.id) << ", pos=" << t.pos << " }";
  }

  using Row = std::string;
  using Grid = std::vector<Row>;

  auto puzzle_08_parse_grid(const Grid& grid)
  {
     const auto result = 
      zip(grid,iota(0))
      | transform([](const auto& ry){
          const auto& [row,y] = ry;
          return 
            zip(row,iota(0))
            | filter([](const auto& cx){return std::get<0>(cx) != '.';})
            | transform([y](const auto& cx){
                const auto& [c,x] = cx;
                return Tower{c,Vec2<int>{x,y}};
              });
        })
      | join;

      return result;
  }

  template <typename TowersIter>
  auto puzzle_08_part1_compute_nulls(TowersIter towers)
  {
    auto result =
      zip(towers,iota(0))
      | transform([towers](const auto& taj){
          const auto& [ta,j] = taj;
          return
            zip(towers,iota(0))
            | filter([j](const auto& tbi){return std::get<1>(tbi) < j;})
            | transform([&ta](const auto& tbi){
                const auto& tb = std::get<0>(tbi);
                const auto& p0 = ta.pos;
                const auto& p1 = tb.pos;
                const auto dp = p1 - p0;
                const auto null_0 = p1 + dp;
                const auto null_1 = p0 - dp;

                return std::ranges::owning_view(std::array{null_0,null_1});
              })
            | join;
        })
      | join;

    return result;
  }

  template <typename TowersIter>
  auto puzzle_08_part1_gather_all_nulls(TowersIter sorted_towers)
  {    
    auto tower_groups = sorted_towers  | chunk_by([](const auto& t1,const auto& t2){return t1.id == t2.id;});
    auto null_groups = tower_groups | transform([](const auto& g){return puzzle_08_part1_compute_nulls(g);});

    auto all_nulls = null_groups | join;

    return all_nulls;
  }


  template <typename TowersIter>
  int puzzle_08_part1_go(TowersIter towers, std::size_t w, std::size_t h)
  {
    auto sorted_towers = towers | std::ranges::to<std::vector>();
    std::ranges::sort(sorted_towers,{},&Tower::id);

    auto all_nulls = 
      puzzle_08_part1_gather_all_nulls(sorted_towers | all)
      | filter([w,h](const auto& v){return v.x>=0 && v.x<w && v.y>=0 && v.y<h;});

    const auto unique_list =
      std::ranges::owning_view(
        std::ranges::fold_left(all_nulls,std::set<Vec2<int>, bool (*)(const Vec2<int>&,const Vec2<int>&)>([](const auto& v0, const auto& v1){return (v0.y<v1.y) || (v0.y==v1.y && v0.x<v1.x);}),[](auto acc, const auto& v){
          acc.insert(v);
          return acc;
        }));

    for (const auto &p : unique_list)
    {
      std::cout << p << std::endl;
    }
    std::cout << "---" << std::endl;

    return unique_list.size();
  }


  int puzzle_08_part1(const std::vector<std::string>& grid)
  {
    auto towers = puzzle_08_parse_grid(grid);
    return puzzle_08_part1_go(towers, grid[0].size(), grid.size());
  }


  int puzzle_08_part2(const std::vector<std::string>& grid)
  {
    return -1;
  }
}



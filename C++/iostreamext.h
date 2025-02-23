#ifndef IOSTREAMEXT_H
#define IOSTREAMEXT_H

#include <iostream>
#include <type_traits>
#include <vector>
#include <tuple>

namespace std //VERY VERY DODGY, but without it, we can't use these inside any custom namespace, only globally, because of ADL
{

  template <typename T, typename ...As>
  std::ostream& operator<<(std::ostream& out, const std::vector<T, As...>& v);
  template <typename T1, typename T2>
  std::ostream& operator<<(std::ostream& out, const std::tuple<T1, T2>& t);


  template <typename T, typename ...As>
  std::ostream& operator<<(std::ostream& out, const std::vector<T, As...>& v)
  {
    bool first_time = true;

    out << "vector<?> {";
    for (const auto& x : v)
    {
      if (!first_time)
      {
        out << ",";
      }
      first_time = false;

      if constexpr (std::is_same_v<std::decay_t<T>,std::string>)
      {
        out << "\"";
        out << x;
        out << "\"";
      }
      else
      {
        out << x;
      }
    }
    out << "}";
    return out;
  }

  template <typename T1, typename T2>
  std::ostream& operator<<(std::ostream& out, const std::tuple<T1, T2>& t)
  {
    out << "tuple<?,?> {";
    out << std::get<0>(t) << ", " << std::get<1>(t);
    out << "}";
    return out;
  }
}
#endif //IOSTREAMEXT_H

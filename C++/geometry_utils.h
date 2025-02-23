#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include <ostream>

namespace geometry_utils
{
  template <typename T>
  struct Vec2
  {
    T x;
    T y;
  };

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const Vec2<T>& v)
  {
    return out << "Vec2{ x=" << v.x << ", y=" << v.y << " }";
  }

  template <typename T>
  Vec2<T> operator+(const Vec2<T>& left, const Vec2<T>& right)
  {
    return Vec2<T>{left.x+right.x, left.y+right.y};
  }
  template <typename T>
  const Vec2<T>& operator+=(Vec2<T>& left, const Vec2<T>& right)
  {
    left = left + right;
    return left;
  }
  template <typename T>
  Vec2<T> operator-(const Vec2<T>& left, const Vec2<T>& right)
  {
    return Vec2{left.x-right.x, left.y-right.y};
  }
  template <typename T>
  const Vec2<T>& operator-=(Vec2<T>& left, const Vec2<T>& right)
  {
    left = left - right;
    return left;
  }
  template <typename T>
  Vec2<T> operator*(const T& s, const Vec2<T>& right)
  {
    return Vec2<T>{s*right.x, s*right.y};
  }
  template <typename T>
  Vec2<T> operator*(const Vec2<T>& left, const T& s)
  {
    return s*left;
  }
  template <typename T>
  Vec2<T> operator/(const Vec2<T>& left, const T& s)
  {
    return Vec2<T>{left.x/s, left.y/s};
  }
}

#endif //GEOMETRY_UTILS_H

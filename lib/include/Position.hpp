#pragma once

#include <cassert>
#include <cmath>
#include <limits>
#include <concepts>

namespace ms_pacman {

template <typename T >
concept integral = std::is_integral_v<T>;

template <typename T >
concept floating_point = std::is_floating_point_v<T>;

template<typename T>
concept number = integral<T> || floating_point<T>;
// This line should be:
// concept number = std::integral<T> || std::floating_point<T>;
// but this is not fully supported in AppleClang currently

template<number T>
struct BasicPosition {
  T x{};
  T y{};
  constexpr BasicPosition() = default;
  constexpr BasicPosition(T x, T y)
    : x(x),
      y(y) {}
};

using Position = BasicPosition<double>;
using GridPosition = BasicPosition<std::size_t>;

inline GridPosition positionToGridPosition(Position pos) {
  assert(pos.x >= 0 && pos.y >= 0 && "Position should have positive values");
  return { size_t(std::round(pos.x)), size_t(std::round(pos.y)) };
}

inline Position gridPositionToPosition(GridPosition pos) {
  return { double(pos.x), double(pos.y) };
}

template<typename T>
inline double positionDistance(const T & a, const T & b) {
  const double first = double(a.x) - double(b.x);
  const double second = double(a.y) - double(b.y);
  return std::sqrt((first * first) + (second * second));
}

template<number T>
bool operator==(const BasicPosition<T> & a,
                const BasicPosition<T> & b) {
  return a.x == b.x && a.y == b.y;
}

template<std::floating_point T>
bool operator==(const BasicPosition<T> & a,
                const BasicPosition<T> & b) {
  constexpr double epsilon =
    std::numeric_limits<double>::epsilon();
  return std::abs(a.x - b.x) <= epsilon &&
         std::abs(a.y - b.y) <= epsilon;
}

} // namespace ms_pacman

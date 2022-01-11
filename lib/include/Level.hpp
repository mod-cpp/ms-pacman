#pragma once
#include <array>
#include <string_view>
#include <tuple>
#include "Mazes.hpp"
#include "Board.hpp"

namespace ms_pacman {

template <typename T, std::size_t Rows, std::size_t Columns>
using array2d = std::array<std::array<T, Columns>, Rows>;

template <typename T>
inline constexpr auto array_extent = std::tuple<>{};

template <typename T, std::size_t N>
constexpr auto array_extent<std::array<T, N>>
  = std::tuple_cat(std::tuple<size_t>(N), array_extent<T>);

template <int N>
struct CellTypeFromValue {};

template <>
struct CellTypeFromValue<0> {
  using type = Wall;
};

template <>
struct CellTypeFromValue<3> {
  using type = Wall;
};

template <>
struct CellTypeFromValue<1> {
  using type = Pellet;
};

template <>
struct CellTypeFromValue<2> {
  using type = Walkable;
};

template <>
struct CellTypeFromValue<4> {
  using type = SuperPellet;
};

template <>
struct CellTypeFromValue<5> {
  using type = Pen;
};

static_assert(std::is_same_v<typename CellTypeFromValue<0>::type, Wall>);

struct Level {
  std::string_view background;
  array2d<int, ROWS, COLUMNS> maze_data;

  constexpr auto create_board() const {
    using B = Board<COLUMNS, ROWS>;
    B b;
    for (std::size_t x = 0; x < COLUMNS; x++) {
      for (std::size_t y = 0; y < ROWS; y++) {
        [&]<int...I>(std::integer_sequence<int, I...>) {
          ([&]<int V>() {
            if(V == maze_data[y][x]) {
              b[y][x] = typename CellTypeFromValue<V>::type{};
            }
          }.template operator()<I>(), ...);
        }(std::make_integer_sequence<int, 6>());
      }
    }
    return b;
  }
};

constexpr std::array levels = {
  Level{ "maze1.png", maze1_data },
  Level{ "maze2.png", maze2_data },
  Level{ "maze3.png", maze3_data },
  Level{ "maze4.png", maze4_data }
};

constexpr Level getLevel(std::size_t n){
    return levels[n];
}

}

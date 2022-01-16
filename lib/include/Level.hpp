#pragma once
#include "Board.hpp"
#include "Mazes.hpp"
#include <array>
#include <string_view>
#include <tuple>

namespace ms_pacman {

template<typename T, std::size_t Rows, std::size_t Columns>
using array2d = std::array<std::array<T, Columns>, Rows>;

template<typename T>
inline constexpr auto array_extent = std::tuple<>{};

template<typename T, std::size_t N>
constexpr auto array_extent<std::array<T, N>> = std::tuple_cat(std::tuple<size_t>(N), array_extent<T>);

struct Level {
  std::string_view background;
  array2d<int, ROWS, COLUMNS> maze_data;
  int num_pellets = count_pellets();

  constexpr int count_pellets() const {
    int pellets = 0;
    for (std::size_t x = 0; x < COLUMNS; x++) {
      for (std::size_t y = 0; y < ROWS; y++) {
        if (maze_data[y][x] == 1 || maze_data[y][x] == 4)
          pellets++;
      }
    }
    return pellets;
  }

  constexpr auto create_board() const {
    using B = Board<COLUMNS, ROWS>;
    B b;
    for (std::size_t x = 0; x < COLUMNS; x++) {
      for (std::size_t y = 0; y < ROWS; y++) {
        switch (maze_data[y][x]) {
          case 0: b[y][x] = Wall{}; break;
          case 1: b[y][x] = Pellet{}; break;
          case 2: b[y][x] = Walkable{}; break;
          case 3: b[y][x] = Wall{}; break;
          case 4: b[y][x] = SuperPellet{}; break;
          case 5: b[y][x] = Pen{}; break;
          case 6: b[y][x] = Portal{0}; break;
          case 7: b[y][x] = Portal{1}; break;
        }
      }
    }
    return b;
  }

  constexpr int getNumPellets() const {
    return num_pellets;
  }
};

constexpr std::array levels = {
  Level{ "maze1.png", maze1_data },
  Level{ "maze2.png", maze2_data },
  Level{ "maze3.png", maze3_data },
  Level{ "maze4.png", maze4_data }
};

constexpr Level getLevel(std::size_t n) {
  return levels[n];
}

} // namespace ms_pacman

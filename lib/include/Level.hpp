#pragma once
#include "Board.hpp"
#include "Mazes.hpp"
#include <array>
#include <optional>
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
    std::array<std::optional<GridPosition>, 4> portals;
    std::size_t idx = 0;

    for (std::size_t x = 0; x < COLUMNS; x++) {
      for (std::size_t y = 0; y < ROWS; y++) {
        switch (maze_data[y][x]) {
          case 0: b[y][x] = Wall{}; break;
          case 1: b[y][x] = Pellet{}; break;
          case 2: b[y][x] = Walkable{}; break;
          case 3: b[y][x] = PenDoor{}; break;
          case 4: b[y][x] = SuperPellet{}; break;
          case 5: b[y][x] = Pen{}; break;
          case 6:
            b[y][x] = Portal{ 0 };
            portals[idx++] = { x, y };
            break;
          case 7:
            b[y][x] = Portal{ 1 };
            portals[idx++] = { x, y };
            break;
        }
      }
    }

    auto getPortal = [&](GridPosition position) -> Portal & {
      return std::get<Portal>(b[position.y][position.x]);
    };

    for (auto && portal_position : portals) {
      if (!portal_position)
        break;

      Portal & portal = getPortal(portal_position.value());
      for (auto && other_position : portals) {
        if (!other_position)
          break;
        if (portal_position == other_position)
          continue;
        Portal & other_portal = getPortal(other_position.value());
        if (portal.id != other_portal.id)
          continue;
        portal.target_position = *other_position;
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
  switch (n) {
    case 0:
    case 1:
      return levels[0];
    case 2:
    case 3:
    case 4:
      return levels[1];
    default:
      // alternate between each of the last 2 maps every 4 levels
      return levels[((n - 5) % 8) < 4 ? 2 : 3];
  }
}

} // namespace ms_pacman

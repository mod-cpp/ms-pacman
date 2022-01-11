#pragma once

#include "Direction.hpp"
#include "Position.hpp"
#include <array>
#include <cstdint>
#include <variant>
#include <vector>

namespace ms_pacman {

const std::size_t ROWS = 31;
const std::size_t COLUMNS = 28;

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

struct Wall {};
struct Walkable {};
struct Pen {};
struct Pellet {
  //
};

struct SuperPellet {
  //
};

struct Portal {
  //
};

using BoardCell = std::variant<Wall, Walkable, Pen, Pellet, SuperPellet, Portal>;

template<std::size_t Columns, std::size_t Rows>
using Board = std::array<std::array<BoardCell, Columns>, Rows>;
using DefaultBoard = Board<COLUMNS, ROWS>;

constexpr static BoardCell cellAtPosition(const DefaultBoard & board, GridPosition point) {
  if (point.x >= COLUMNS || point.y >= ROWS)
    return Wall{};
  return board[point.y][point.x];
}

constexpr bool isWalkableForPacMan(const DefaultBoard & board, GridPosition point) {
  BoardCell cell = cellAtPosition(board, point);
  return std::visit(overloaded{
                      [](const Wall &) { return false; },
                      [](const Pen &) { return false; },
                      [](const auto &) { return true; } },
                    cell);
}

constexpr bool isInPen(const DefaultBoard & board, GridPosition point) {
  BoardCell cell = cellAtPosition(board, point);
  return std::visit(overloaded{
                      [](const Pen &) { return true; },
                      [](const auto &) { return false; } },
                    cell);
}

constexpr bool isWalkableForGhost(const DefaultBoard & board, GridPosition target_position, GridPosition current_position, bool isEyes) {
  BoardCell cell = cellAtPosition(board, target_position);
  return std::visit(overloaded{
                      [](const Wall &) { return false; },
                      [&](const Pen &) { return isEyes || isInPen(board, current_position); },
                      [](const auto &) { return true; } },
                    cell);
}

constexpr bool isPortal(const DefaultBoard &, GridPosition, Direction) {
  return false;
}

constexpr GridPosition teleport(GridPosition point) {
  return point;
}

inline Position penDoorPosition() {
  return { 13, 11 };
}

inline Position initialPacManPosition() {
  return { 13.5, 23 };
}

} // namespace ms_pacman

#pragma once

#include "Direction.hpp"
#include "Position.hpp"
#include <array>
#include <cstdint>
#include <optional>
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
struct PenDoor {};
struct Pellet {};
struct SuperPellet {};
struct Portal {
  int id;
  GridPosition target_position = {};
};

using BoardCell = std::variant<Wall, Walkable, Pen, PenDoor, Pellet, SuperPellet, Portal>;

template<std::size_t Columns, std::size_t Rows>
using Board = std::array<std::array<BoardCell, Columns>, Rows>;
using DefaultBoard = Board<COLUMNS, ROWS>;
using Portals = std::array<std::optional<GridPosition>, 4>;

constexpr static BoardCell cellAtPosition(const DefaultBoard & board, GridPosition point) {
  if (point.x >= COLUMNS || point.y >= ROWS)
    return Wall{};
  return board[point.y][point.x];
}

constexpr bool isWalkableForMsPacMan(const DefaultBoard & board, GridPosition point) {
  BoardCell cell = cellAtPosition(board, point);
  return std::visit(overloaded{
                      [](const Wall &) { return false; },
                      [](const Pen &) { return false; },
                      [](const PenDoor &) { return false; },
                      [](const auto &) {
                        return true;
                      } },
                    cell);
}

constexpr bool isInPen(const DefaultBoard & board, GridPosition point) {
  BoardCell cell = cellAtPosition(board, point);
  return std::visit(overloaded{
                      [](const Pen &) { return true; },
                      [](const auto &) {
                        return false;
                      } },
                    cell);
}

constexpr bool isWalkableForGhost(const DefaultBoard & board, GridPosition current_position, GridPosition target_position, bool isEyes) {
  BoardCell cell = cellAtPosition(board, target_position);
  return std::visit(overloaded{
                      [](const Wall &) { return false; },
                      [&](const Pen &) { return isEyes || isInPen(board, current_position); },
                      [](const auto &) {
                        return true;
                      } },
                    cell);
}

constexpr bool shouldTeleport(const DefaultBoard & board, GridPosition position, Direction direction) {
  BoardCell cell = cellAtPosition(board, position);
  return std::visit(overloaded{
                      [&position, &direction](const Portal &) {
                        bool enteringLeftPortal = position.x < (COLUMNS / 2) && direction == Direction::LEFT;
                        bool enteringRightPortal = position.x > (COLUMNS / 2) && direction == Direction::RIGHT;
                        return enteringLeftPortal || enteringRightPortal;
                      },
                      [](const auto &) {
                        return false;
                      } },
                    cell);
}

constexpr GridPosition teleport(const DefaultBoard & board, GridPosition position) {
  BoardCell cell = cellAtPosition(board, position);
  if (std::holds_alternative<Portal>(cell)) {
    return std::get<Portal>(cell).target_position;
  }
  return position;
}

inline Position penDoorPosition() {
  return { 13, 11 };
}

inline Position initialPacManPosition() {
  return { 13.5, 23 };
}

} // namespace ms_pacman

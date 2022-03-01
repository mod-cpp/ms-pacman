#pragma once

#include "Board.hpp"

#include <algorithm>
#include <chrono>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

namespace ms_pacman {

class NPC {
public:
  NPC(const Position position, const Position scatterTarget)
    : pos(position),
      target(scatterTarget) {}
  NPC(const Position targetPos, bool stop)
    : pos(targetPos),
      target(targetPos),
      stop_at_target(stop) {}
  virtual ~NPC() = default;

  virtual double speed() const = 0;
  virtual bool isWalkable(const DefaultBoard & board, GridPosition current_position, GridPosition target_position) const = 0;

  void updatePosition(std::chrono::milliseconds time_delta, const DefaultBoard & board) {

    if (stop_at_target && isSamePosition(positionInGrid(), targetInGrid()))
      return;

    updateDirection(board);

    double position_delta = (0.004 * double(time_delta.count())) * speed();

    const auto old_position = pos;
    const GridPosition old_grid_position = positionToGridPosition(old_position);

    switch (direction) {
      case Direction::NONE:
        break;
      case Direction::LEFT:
        pos.x -= position_delta;
        pos.y = round(pos.y);
        break;
      case Direction::RIGHT:
        pos.x += position_delta;
        pos.y = round(pos.y);
        break;
      case Direction::UP:
        pos.x = round(pos.x);
        pos.y -= position_delta;
        break;
      case Direction::DOWN:
        pos.x = round(pos.x);
        pos.y += position_delta;
        break;
    }

    if (shouldTeleport(board, positionInGrid(), direction)) {
      pos = gridPositionToPosition(teleport(board, positionInGrid()));
    } else if (!isWalkable(board, old_grid_position, positionInGrid())) {
      pos = old_position;
      direction = oppositeDirection(direction);
    }
  }

  /*
   *  Each time a npc finds itself at an intersection,
   *  it picks a target position - the specific target depends on the state
   *  of the npc and the specific npc.
   *
   *  For each 4 cells around the current npc position the straight-line distance
   *  to the target is calculated (this ignores all obstacles, including walls)
   *
   *  The npc then selects among these 4 cells the one with the shortest euclidean distance to the target.
   *  If a cell is a wall or would cause a npc to move in the opposite direction, the distance to the target
   *  from that cell is considered infinite (due to the shape of the maze, there is always one direction
   *  a npc can take).
   *
   *  In the scatter state, each npc tries to reach an unreachable position outside of the map.
   *  This makes npcs run in circle around the island at each of the 4 map corner.
   */
  void updateDirection(const DefaultBoard & board) {
    const auto current_grid_position = positionInGrid();
    if (isSamePosition(current_grid_position, last_grid_position))
      return;

    struct Move {
      Direction direction = Direction::NONE;
      Position position;
      double distance_to_target = std::numeric_limits<double>::infinity();
    };

    const auto [x, y] = gridPositionToPosition(current_grid_position);
    std::array<Move, 4> possible_moves = {
      Move{ Direction::UP, { x, y - 1 } },
      Move{ Direction::LEFT, { x - 1, y } },
      Move{ Direction::DOWN, { x, y + 1 } },
      Move{ Direction::RIGHT, { x + 1, y } }
    };

    auto set_teleport = [&](const auto & move) {
      Move transformed = move;
      if (shouldTeleport(board, current_grid_position, move.direction))
        transformed.position = gridPositionToPosition(teleport(board, current_grid_position));
      return transformed;
    };

    auto has_valid_position = [](const auto & move) {
      return !(move.position.x < 0 || move.position.y < 0);
    };

    auto has_valid_direction = [&](const auto & move) {
      return !(move.direction == oppositeDirection(direction));
    };

    auto is_allowed_move = [&](const auto & move) {
      const GridPosition grid_position = { size_t(move.position.x), size_t(move.position.y) };
      return isWalkable(board, current_grid_position, grid_position);
    };

    auto set_distance_to_target = [&](const auto & move) {
      Move transformed = move;
      transformed.distance_to_target = std::hypot(move.position.x - target.x, move.position.y - target.y);
      return transformed;
    };

    auto view = possible_moves
                | std::views::transform(set_teleport)
                | std::views::filter(has_valid_position)
                | std::views::filter(has_valid_direction)
                | std::views::filter(is_allowed_move)
                | std::views::transform(set_distance_to_target);

    if (std::ranges::empty(view))
      return;

    const auto optimal_move = std::ranges::min_element(view, {}, &Move::distance_to_target);

    const auto & move = *optimal_move;
    direction = move.direction;
    last_grid_position = current_grid_position;
  }

  Position position() const {
    return pos;
  }

  void setPosition(Position p) {
    pos = p;
  }

  GridPosition positionInGrid() const {
    return positionToGridPosition(pos);
  }

  Position targetPosition() const {
    return target;
  }

  GridPosition targetInGrid() const {
    return positionToGridPosition(target);
  }

protected:
  Position pos{};
  Direction direction = Direction::NONE;
  GridPosition last_grid_position = { 0, 0 };
  Position target{};
  bool stop_at_target = false;
};

} // namespace ms_pacman

#pragma once

#include "Board.hpp"
#include <chrono>
namespace ms_pacman {

class NPC {
public:
  NPC(const Position position, const Position scatterTarget)
    : pos(position),
      target(scatterTarget) {}
  virtual ~NPC() = default;

  virtual double speed() const = 0;
  virtual bool isWalkable(const DefaultBoard & board, GridPosition current_position, GridPosition target_position) const = 0;

  void updatePosition(std::chrono::milliseconds time_delta, const DefaultBoard & board) {
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

    for (auto & move : possible_moves) {
      if (shouldTeleport(board, current_grid_position, move.direction))
        move.position = gridPositionToPosition(teleport(board, current_grid_position));

      const bool invalid_position = (move.position.x < 0 || move.position.y < 0);
      if (invalid_position)
        continue;

      const bool opposite_direction = (move.direction == oppositeDirection(direction));
      if (opposite_direction)
        continue;

      const GridPosition grid_position = { size_t(move.position.x), size_t(move.position.y) };
      const bool can_walk = isWalkable(board, current_grid_position, grid_position);
      if (!can_walk)
        continue;

      move.distance_to_target = std::hypot(move.position.x - target.x, move.position.y - target.y);
    }

    const auto optimal_move = std::min_element(possible_moves.begin(), possible_moves.end(), [](const auto & a, const auto & b) {
      return a.distance_to_target < b.distance_to_target;
    });

    const auto & move = *optimal_move;
    direction = move.direction;
    last_grid_position = current_grid_position;
  }

  Position position() const {
    return pos;
  }

  GridPosition positionInGrid() const {
    return positionToGridPosition(pos);
  }

protected:
  Position pos;
  Direction direction = Direction::NONE;
  GridPosition last_grid_position = { 0, 0 };
  Position target;
};

} // namespace ms_pacman

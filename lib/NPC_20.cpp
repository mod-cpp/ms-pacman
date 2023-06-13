#include "NPC.hpp"

#include <algorithm>

namespace ms_pacman {

void NPC::updateDirection(const DefaultBoard & board) {
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

} // namespace ms_pacman

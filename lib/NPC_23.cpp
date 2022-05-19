#include "NPC.hpp"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

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
    return move.direction != oppositeDirection(direction);
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

  auto valid_moves = possible_moves                            //
                     | std::views::transform(set_teleport)     //
                     | std::views::filter(has_valid_position)  //
                     | std::views::filter(has_valid_direction) //
                     | std::views::filter(is_allowed_move)     //
                     | std::views::transform(set_distance_to_target);

  if (std::ranges::empty(valid_moves))
    return;

  const auto optimal_move = std::ranges::min_element(valid_moves, {}, &Move::distance_to_target);

  const auto & move = *optimal_move;
  direction = move.direction;
  last_grid_position = current_grid_position;
}

} // namespace ms_pacman

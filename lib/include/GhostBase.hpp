#pragma once

#include "AtlasGhosts.hpp"
#include "Board.hpp"
#include "GhostState.hpp"
#include "MsPacMan.hpp"
#include <numeric>

namespace ms_pacman {

template<typename Ghost>
class GhostBase {
public:
  GhostBase(const Atlas::Ghost spriteSet, const Position position, const Position scatterTarget)
    : pos(position),
      spriteSet(spriteSet),
      target(scatterTarget) {}

  constexpr double speed() const {
    if (state == GhostState::Eyes)
      return 2;
    if (state == GhostState::Frightened)
      return 0.5;
    return 0.75;
  }

  constexpr bool isInPen(const DefaultBoard & board) const {
    return ms_pacman::isInPen(board, positionInGrid());
  }

  Position position() const {
    return pos;
  }

  GridPosition positionInGrid() const {
    return positionToGridPosition(pos);
  }

  bool isFrightened() const {
    return state == GhostState::Frightened;
  }

  bool isEyes() const {
    return state == GhostState::Eyes;
  }

  GridPosition currentSprite() const {
    switch (state) {
      default:
        return Atlas::ghostSprite(spriteSet, direction, (animationIndex % 2) == 0);
      case GhostState::Eyes:
        return Atlas::eyeSprite(direction);
      case GhostState::Frightened:
        if (timeFrighten.count() < 3500)
          return Atlas::initialFrightened(animationIndex);
        else
          return Atlas::endingFrightened(animationIndex);
    }
  }

  void update(std::chrono::milliseconds time_delta, const DefaultBoard & board) {
    if (state == GhostState::Eyes && isInPen(board)) {
      state = GhostState::Scatter;
    }

    if (state == GhostState::Frightened) {
      timeFrighten += time_delta;
      if (timeFrighten.count() > 6000)
        state = GhostState::Scatter;
    }

    if (state == GhostState::Scatter || state == GhostState::Chase) {
      timeChase += time_delta;
      const auto newState = defaultStateAtDuration(std::chrono::duration_cast<std::chrono::seconds>(timeChase));
      if (newState != state) {
        direction = oppositeDirection(direction);
        state = newState;
      }
    }

    updateAnimation(time_delta);
    updatePosition(time_delta, board);
  }

  GhostState defaultStateAtDuration(std::chrono::seconds seconds) const {
    // This array denotes the duration of each state, alternating between scatter and chase
    std::array changes = { /*scatter*/ 7, 20, 7, 20, 5, 20, 5 };

    // To know the current state we first compute the cumulative time using std::partial_sum
    // This gives us {7, 27, 34, 54, 59, 79, 84}
    std::partial_sum(std::begin(changes), std::end(changes), std::begin(changes));

    // Then we look for the first value in the array greater than the time spent in chase/scatter states
    auto it = std::upper_bound(std::begin(changes), std::end(changes), seconds.count());

    // We get the position of that iterator in the array
    auto count = std::distance(std::begin(changes), it);

    // Because the first position is scatter, all the even positions will be "scatter"
    // all the odd positions will be "chase"
    return count % 2 == 0 ? GhostState::Scatter : GhostState::Chase;
  }

  void updateAnimation(std::chrono::milliseconds time_delta) {
    timeForAnimation += double(time_delta.count());
    if (timeForAnimation >= 250) {
      timeForAnimation = 0;
      animationIndex = (animationIndex + 1) % 4;
    }
  }

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
    } else if (!isWalkableForGhost(board, old_grid_position, positionInGrid(), isEyes())) {
      pos = old_position;
      direction = oppositeDirection(direction);
    }
  }

  /*
   *  Each time a ghost finds itself at an intersection,
   *  it picks a target position - the specific target depends on the state
   *  of the ghost and the specific ghost.
   *
   *  For each 4 cells around the current ghost position the straight-line distance
   *  to the target is calculated (this ignores all obstacles, including walls)
   *
   *  The ghost then selects among these 4 cells the one with the shortest euclidean distance to the target.
   *  If a cell is a wall or would cause a ghost to move in the opposite direction, the distance to the target
   *  from that cell is considered infinite (due to the shape of the maze, there is always one direction
   *  a ghost can take).
   *
   *  In the scatter state, each ghost tries to reach an unreachable position outside of the map.
   *  This makes ghosts run in circle around the island at each of the 4 map corner.
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
      const bool can_walk = isWalkableForGhost(board, current_grid_position, grid_position, isEyes());
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

  void die() {
    if (state == GhostState::Eyes)
      return;

    direction = oppositeDirection(direction);
    state = GhostState::Eyes;
    timeFrighten = {};
    timeChase = {};
  }

  void reset() {
    pos = Ghost::initialPosition;
    state = GhostState::Scatter;
    timeFrighten = {};
    timeChase = {};
  }

  void frighten() {
    if (state > GhostState::Scatter)
      return;

    direction = oppositeDirection(direction);
    state = GhostState::Frightened;
    timeFrighten = {};
  }

protected:
  GhostState state = GhostState::Chase;
  Position pos;
  Atlas::Ghost spriteSet;
  Direction direction = Direction::NONE;
  double timeForAnimation = 0;
  std::size_t animationIndex = 0;
  std::chrono::milliseconds timeFrighten = {};
  std::chrono::milliseconds timeChase = {};
  GridPosition last_grid_position = { 0, 0 };
  Position target;
};

} // namespace ms_pacman

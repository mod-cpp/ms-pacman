#pragma once

#include "Direction.hpp"
#include "Position.hpp"
#include <cassert>

#include <array>

namespace ms_pacman::Atlas {

enum class Ghost : unsigned int {
  blinky = 2,
  pinky = 3,
  inky = 4,
  clyde = 5,
};

constexpr GridPosition pacman_right_wide = { 2, 1 };
constexpr GridPosition pacman_right_narrow = { 1, 1 };
constexpr GridPosition pacman_right_closed = { 3, 1 };
constexpr GridPosition pacman_left_narrow = { 6, 0 };
constexpr GridPosition pacman_left_wide = { 7, 0 };
constexpr GridPosition pacman_left_closed = { 0, 1 };
constexpr GridPosition pacman_up_wide = { 1, 0 };
constexpr GridPosition pacman_up_narrow = { 0, 0 };
constexpr GridPosition pacman_up_closed = { 2, 0 };
constexpr GridPosition pacman_down_wide = { 4, 0 };
constexpr GridPosition pacman_down_narrow = { 3, 0 };
constexpr GridPosition pacman_down_closed = { 5, 0 };

constexpr GridPosition ghost_blue_frightened = { 4, 1 };
constexpr GridPosition ghost_blue_frightened2 = { 5, 1 };
constexpr GridPosition ghost_white_frightened = { 6, 1 };
constexpr GridPosition ghost_white_frightened2 = { 7, 1 };

constexpr GridPosition fruit_cherry = { 0, 6 };
constexpr GridPosition fruit_strawberry = { 1, 6 };
constexpr GridPosition fruit_orange = { 2, 6 };
constexpr GridPosition fruit_pretzel = { 3, 6 };
constexpr GridPosition fruit_apple = { 4, 6 };
constexpr GridPosition fruit_pear = { 5, 6 };
constexpr GridPosition fruit_banana = { 6, 6 };

constexpr GridPosition eyeSprite(Direction direction) {
  switch (direction) {
    case Direction::RIGHT:
      return { 7, 7 };
    case Direction::DOWN:
      return { 5, 7 };
    case Direction::LEFT:
      return { 6, 7 };
    case Direction::UP:
      return { 4, 7 };
    default:
      return { 7, 7 };
  }
}

constexpr GridPosition ghostSprite(Ghost ghost, Direction direction, bool alternative) {
  assert(ghost >= Ghost::blinky && ghost <= Ghost::clyde && "Invalid Ghost");
  auto y = static_cast<size_t>(ghost);
  size_t x = 0;
  switch (direction) {
    case Direction::RIGHT:
      x = 0;
      break;
    case Direction::DOWN:
      x = 2;
      break;
    case Direction::LEFT:
      x = 4;
      break;
    case Direction::UP:
      x = 6;
      break;
    default:
      x = 0;
      break;
  }
  if (alternative)
    x++;
  return { x, y };
}

constexpr GridPosition initialFrightened(std::size_t animationIndex) {
  return (animationIndex % 2) == 0 ? Atlas::ghost_blue_frightened2 : Atlas::ghost_blue_frightened;
}

constexpr GridPosition endingFrightened(std::size_t animationIndex) {
  std::array<GridPosition, 4> positions = { Atlas::ghost_blue_frightened,
                                            Atlas::ghost_blue_frightened2,
                                            Atlas::ghost_white_frightened,
                                            Atlas::ghost_white_frightened2 };
  return positions[animationIndex];
}
} // namespace ms_pacman::Atlas

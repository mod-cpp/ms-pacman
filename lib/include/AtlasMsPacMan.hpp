#pragma once

#include "Direction.hpp"
#include "Position.hpp"

#include <array>

namespace ms_pacman::Atlas {

struct MsPacManAnimation {
  size_t position = 0;
  double delta = 0.0;
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

constexpr std::array<GridPosition, 4> down_animation{ pacman_down_wide, pacman_down_narrow, pacman_down_closed, pacman_down_narrow };
constexpr std::array<GridPosition, 4> left_animation{ pacman_left_wide, pacman_left_narrow, pacman_left_closed, pacman_left_narrow };
constexpr std::array<GridPosition, 4> right_animation{ pacman_right_wide, pacman_right_narrow, pacman_right_closed, pacman_right_narrow };
constexpr std::array<GridPosition, 4> up_animation{ pacman_up_wide, pacman_up_narrow, pacman_up_closed, pacman_up_narrow };
constexpr std::array<GridPosition, 4> death_animation{ pacman_left_narrow, pacman_up_narrow, pacman_right_narrow, pacman_down_narrow };

constexpr GridPosition animationFrame(const MsPacManAnimation & animation, Direction direction) {
  switch (direction) {
    case Direction::LEFT:
      return left_animation[animation.position];
    case Direction::RIGHT:
      return right_animation[animation.position];
    case Direction::UP:
      return up_animation[animation.position];
    case Direction::DOWN:
      return down_animation[animation.position];
    case Direction::NONE:
    default:
      return Atlas::pacman_left_narrow;
  }
}

constexpr GridPosition deathAnimationFrame(const MsPacManAnimation & animation) {
  return death_animation[animation.position];
}

constexpr void updateAnimationPosition(MsPacManAnimation & animation, std::chrono::milliseconds time_delta, bool dead) {
  if (dead && animation.position >= 11)
    return;

  animation.delta += (0.01) * double(time_delta.count());
  animation.position += size_t(animation.delta);
  animation.position = animation.position % 4;

  if (animation.delta > 1)
    animation.delta = animation.delta - 1;
}

constexpr void pause(MsPacManAnimation & animation) {
  // when hitting a wall, MsPacman's mouth stays wide open
  animation.position = 0;
  animation.delta = 0;
}

} // namespace ms_pacman::Atlas

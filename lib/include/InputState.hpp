#pragma once

#include "Direction.hpp"

namespace ms_pacman {

class InputState {
public:
  bool close = false;
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool enableAI = false;

  constexpr Direction direction() const {
    if (up)
      return Direction::UP;
    if (down)
      return Direction::DOWN;
    if (left)
      return Direction::LEFT;
    if (right)
      return Direction::RIGHT;
    return Direction::NONE;
  }
};

} // namespace pacman

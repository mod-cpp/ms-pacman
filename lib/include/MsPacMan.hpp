#pragma once

#include "AtlasMsPacMan.hpp"
#include "Board.hpp"
#include "Direction.hpp"
#include "Position.hpp"

#include <chrono>

namespace ms_pacman {

class MsPacMan {
public:
  GridPosition currentSprite() const;
  Position position() const;
  GridPosition positionInGrid() const;

  void update(std::chrono::milliseconds time_delta, Direction input_direction, const DefaultBoard & board);

  void die();
  void reset();
  bool hasDirection() const {
    return direction != Direction::NONE;
  }

  Direction currentDirection() const {
    return direction;
  }

  void eat(const SuperPellet & superPellet);

private:
  Direction direction = Direction::NONE;
  Direction desired_direction = Direction::NONE;
  Position pos = initialPacManPosition();
  Atlas::MsPacManAnimation pacManAnimation;
  bool dead = false;

  void updateAnimationPosition(std::chrono::milliseconds time_delta, bool paused);
  void updateMazePosition(std::chrono::milliseconds time_delta, const DefaultBoard & board);
};

} // namespace ms_pacman

#pragma once

#include "GhostBase.hpp"

namespace ms_pacman {

// Curiously Recurring Template Pattern CRTP
struct Pinky : public GhostBase<Pinky> {

  Pinky()
    : GhostBase<Pinky>(initialSpriteSet, initialPosition, scatterTarget) {}

  static constexpr Atlas::Ghost initialSpriteSet = Atlas::Ghost::pinky;
  static constexpr Position initialPosition = Position{ 11.5, 14 };
  static constexpr Position scatterTarget = Position{ 3, -2 };

  void setTarget(const DefaultBoard & board, const MsPacMan & msPacMan, const GridPosition &) {

    if (state == GhostState::Eyes) {
      target = initialPosition;
      return;
    }

    if (isInPen(board)) {
      target = penDoorPosition();
      return;
    }

    if (state == GhostState::Scatter) {
      target = scatterTarget;
      return;
    }

    // Inky first selects a position 2 cell away from pacman in his direction.
    GridPosition targetPosition = msPacMan.positionInGrid();
    switch (msPacMan.currentDirection()) {
      case Direction::LEFT:
        targetPosition.x -= 4;
        break;
      case Direction::RIGHT:
        targetPosition.x += 4;
        break;
      case Direction::UP:
        targetPosition.y -= 4;
        targetPosition.x -= 4;
        break;
      case Direction::DOWN:
        targetPosition.y += 4;
        break;
      case Direction::NONE:
        assert(false && "Pacman should be moving");
        break;
    }

    target = gridPositionToPosition(targetPosition);
  }
};

// Curiously Recurring Template Pattern CRTP
struct Inky : public GhostBase<Inky> {

  Inky()
    : GhostBase<Inky>(initialSpriteSet, initialPosition, scatterTarget) {}

  static constexpr Atlas::Ghost initialSpriteSet = Atlas::Ghost::inky;
  static constexpr Position initialPosition = Position{ 13.5, 14 };
  static constexpr Position scatterTarget = Position{ 27, 30 };

  void setTarget(const DefaultBoard & board, const MsPacMan & msPacMan, const GridPosition & blinkyPos) {
    if (state == GhostState::Eyes) {
      target = initialPosition;
      return;
    }

    if (isInPen(board)) {
      target = penDoorPosition();
      return;
    }

    if (state == GhostState::Scatter) {
      target = scatterTarget;
      return;
    }

    // Inky first selects a position 2 cell away from pacman in his direction.
    GridPosition targetPosition = msPacMan.positionInGrid();
    switch (msPacMan.currentDirection()) {
      case Direction::LEFT:
        targetPosition.x -= 2;
        break;
      case Direction::RIGHT:
        targetPosition.x += 2;
        break;
      case Direction::UP:
        targetPosition.y -= 2;
        targetPosition.x -= 2;
        break;
      case Direction::DOWN:
        targetPosition.y += 2;
        break;
      case Direction::NONE:
        assert(false && "Ms. Pacman should be moving");
        break;
    }

    // Then it calculates the distance between Blinky and this position
    const double distanceBetweenBlinkyAndTarget = std::hypot(blinkyPos.x - targetPosition.x, blinkyPos.y - targetPosition.y);

    // And selects a point on the line crossing blinky and
    // this position that is at twice that distance away from blinky
    targetPosition.x += std::size_t((double(targetPosition.x) - double(blinkyPos.x)) / distanceBetweenBlinkyAndTarget) * 2;
    targetPosition.y += std::size_t((double(targetPosition.y) - double(blinkyPos.y)) / distanceBetweenBlinkyAndTarget) * 2;

    target = gridPositionToPosition(targetPosition);
  }
};

// Curiously Recurring Template Pattern CRTP
struct Blinky : public GhostBase<Blinky> {

  Blinky()
    : GhostBase<Blinky>(initialSpriteSet, initialPosition, scatterTarget) {}

  static constexpr Atlas::Ghost initialSpriteSet = Atlas::Ghost::blinky;
  static constexpr Position initialPosition = Position{ 13.5, 11 };
  static constexpr Position scatterTarget = Position{ 25, -3 };

  void setTarget(const DefaultBoard & board, const MsPacMan & msPacMan, const GridPosition &) {
    if (state == GhostState::Eyes) {
      target = Inky::initialPosition;
      return;
    }

    if (isInPen(board)) {
      target = penDoorPosition();
      return;
    }

    target = state == GhostState::Chase ? msPacMan.position() : scatterTarget;
  }
};

// Curiously Recurring Template Pattern CRTP
struct Sue : public GhostBase<Sue> {

  Sue()
    : GhostBase<Sue>(initialSpriteSet, initialPosition, scatterTarget) {}

  static constexpr Atlas::Ghost initialSpriteSet = Atlas::Ghost::sue;
  static constexpr Position initialPosition = Position{ 15.5, 14 };
  static constexpr Position scatterTarget = Position{ 0, 30 };

  void setTarget(const DefaultBoard & board, const MsPacMan & msPacMan, const GridPosition &) {

    if (state == GhostState::Eyes) {
      target = initialPosition;
      return;
    }

    if (isInPen(board)) {
      target = penDoorPosition();
      return;
    }

    // Clyde always target its scatter target, unless pacman is further than 8 tiles away
    target = scatterTarget;
    if (state == GhostState::Scatter) {
      return;
    }

    Position msPacManPos = msPacMan.position();
    const auto distanceFomPacMan = std::hypot(pos.x - msPacManPos.x, pos.y - msPacManPos.y);
    if (distanceFomPacMan > 8) {
      target = msPacManPos;
    }
  }
};

} // namespace ms_pacman

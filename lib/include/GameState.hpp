#pragma once

#include <tuple>

#include "Fruit.hpp"
#include "Ghost.hpp"
#include "GhostName.hpp"
#include "InputState.hpp"
#include "Level.hpp"
#include "MsPacMan.hpp"
#include "Score.hpp"

namespace ms_pacman {

constexpr int GHOST_POINTS = 200;

using Blinky = Ghost<GhostName::Blinky>;
using Pinky = Ghost<GhostName::Pinky>;
using Inky = Ghost<GhostName::Inky>;
using Clyde = Ghost<GhostName::Clyde>;
using Ghosts = std::tuple<Blinky, Pinky, Inky, Clyde>;

struct GameState {
  void step(std::chrono::milliseconds delta);

  Ghosts ghosts;
  MsPacMan msPacMan;
  InputState inputState;
  GenericFruit currentFruit;
  size_t levelNum = 0;
  Level level = getLevel(levelNum);
  DefaultBoard board;

  Score score;
  std::chrono::milliseconds timeSinceDeath{};

  template<GhostName Name>
  void checkCollision(Ghost<Name> & ghost) {
    if (isMsPacManDying() || ghost.isEyes())
      return;

    // TODO: hitboxes based collision
    if (ghost.positionInGrid() != msPacMan.positionInGrid())
      return;

    if (ghost.isFrightened()) {
      ghost.die();
      score.points += GHOST_POINTS;
    } else {
      killMsPacMan();
    }
  }

  void handleDeathAnimation(std::chrono::milliseconds delta);
  void eatPellets();
  void eatFruit();
  void killMsPacMan();
  bool isMsPacManDying() const;
  void increaseLevel();
  bool isLevelCompleted() const;
  void reset();
};

} // namespace ms_pacman

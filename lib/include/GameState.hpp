#pragma once

#include <tuple>

#include "Blinky.hpp"
#include "Fruit.hpp"
#include "Inky.hpp"
#include "InputState.hpp"
#include "Level.hpp"
#include "MsPacMan.hpp"
#include "Pinky.hpp"
#include "Score.hpp"

namespace ms_pacman {

using Ghosts = std::tuple<Blinky, Pinky, Inky>;

struct GameState {
  void step(std::chrono::milliseconds delta);

  Ghosts ghosts;
  MsPacMan pacMan;
  InputState inputState;
  GenericFruit currentFruit;
  Level level = getLevel(0);
  DefaultBoard board;

  Score score;
  std::chrono::milliseconds timeSinceDeath{};

  void checkCollision(Ghost & ghost);
  void handleDeathAnimation(std::chrono::milliseconds delta);
  void eatPellets();
  void eatFruit();
  void killPacMan();
  bool isPacManDying() const;
};

} // namespace ms_pacman

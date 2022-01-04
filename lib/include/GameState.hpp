#pragma once

#include <tuple>

#include "Blinky.hpp"
#include "Fruits.hpp"
#include "Inky.hpp"
#include "InputState.hpp"
#include "MsPacMan.hpp"
#include "Pellets.hpp"
#include "Pinky.hpp"
#include "Score.hpp"
#include "SuperPellets.hpp"
#include "Level.hpp"

namespace ms_pacman {

struct GameState {
  void step(std::chrono::milliseconds delta);

  std::tuple<Blinky, Pinky, Inky> ghosts;

  MsPacMan pacMan;
  InputState inputState;
  Pellets pellets;
  SuperPellets superPellets;
  Fruits fruit;
  Level  level = getLevel(0);
  Score score;
  std::chrono::milliseconds timeSinceDeath{};

  void checkCollision(Ghost & ghost);
  void handleDeathAnimation(std::chrono::milliseconds delta);
  void eatPellets();
  void eatFruit();
  void killPacMan();
  bool isPacManDying() const;
};

} // namespace pacman

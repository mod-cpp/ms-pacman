#pragma once

#include <tuple>

#include "Blinky.hpp"
#include "Fruits.hpp"
#include "Inky.hpp"
#include "InputState.hpp"
#include "PacMan.hpp"
#include "Pellets.hpp"
#include "Pinky.hpp"
#include "Score.hpp"
#include "SuperPellets.hpp"

namespace pacman {

struct GameState {
  void step(std::chrono::milliseconds delta);

  std::tuple<Blinky, Pinky, Inky> ghosts;

  PacMan pacMan;
  InputState inputState;
  Pellets pellets;
  SuperPellets superPellets;
  Fruits fruit;

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

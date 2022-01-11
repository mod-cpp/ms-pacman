#pragma once

#include <tuple>

#include "Blinky.hpp"
#include "Fruit.hpp"
#include "Inky.hpp"
#include "InputState.hpp"
#include "MsPacMan.hpp"
#include "Pinky.hpp"
#include "Score.hpp"
#include "Level.hpp"

namespace ms_pacman {

struct GameState {
  void step(std::chrono::milliseconds delta);

  std::tuple<Blinky, Pinky, Inky> ghosts;

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

} // namespace pacman

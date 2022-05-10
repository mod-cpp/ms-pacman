#pragma once

#include "Canvas.hpp"
#include "Cheats.hpp"
#include "GameState.hpp"
#include "InputState.hpp"

namespace ms_pacman {

class Game {
public:
  void run();

private:
  Canvas canvas;
  GameState gameState;
  Cheats cheats;

  void loadLevel();
  void processEvents(InputState & key);
};

} // namespace ms_pacman

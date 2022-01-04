#pragma once

#include "GameState.hpp"
#include "InputState.hpp"
#include "Canvas.hpp"

namespace ms_pacman {

class Game {
public:
  void run();

private:
  Canvas canvas;
  GameState gameState;

  void loadLevel();
  void processEvents(InputState & inputState);
};

} // namespace pacman

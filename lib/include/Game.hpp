#pragma once

#include "Canvas.hpp"
#include "GameState.hpp"
#include "InputState.hpp"

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

} // namespace ms_pacman

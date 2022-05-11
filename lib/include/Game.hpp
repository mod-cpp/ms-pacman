#pragma once

#include "Canvas.hpp"
#include "GameState.hpp"
#include "InputHandler.hpp"
#include "InputState.hpp"

namespace ms_pacman {

class Game {
public:
  void run();

private:
  Canvas canvas;
  GameState gameState;
  InputHandler inputHandler;

  void loadLevel();
  void processEvents(InputState & key);
};

} // namespace ms_pacman

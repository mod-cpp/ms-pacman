#pragma once

#include "Canvas.hpp"
#include "GameState.hpp"
#include "InputState.hpp"

namespace ms_pacman {

class Game {
public:
  void run();
  ~Game();

private:
  Canvas canvas;
  GameState gameState;

  void loadLevel();
  void processEvents(InputState & inputState);

  int loadBestScore() const;
  void saveScore(int) const;
};

} // namespace ms_pacman

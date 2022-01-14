#pragma once

namespace ms_pacman {

constexpr int DEFAULT_LIVES = 3;

struct Score {
  int lives = DEFAULT_LIVES;
  int points = 0;
  int eatenPellets = 0;
  std::vector<GenericFruit> eatenFruits;
  constexpr void reset() {
    eatenPellets = 0;
  }
};

} // namespace ms_pacman

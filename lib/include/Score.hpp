#pragma once

#include <vector>

#include "Fruit.hpp"

namespace ms_pacman {

constexpr int DEFAULT_LIVES = 3;

struct Score {
  int lives = DEFAULT_LIVES;
  int points = 0;
  int eatenPellets = 0;
  std::vector<GenericFruit> eatenFruits;
};

} // namespace ms_pacman

#pragma once

#include <vector>

#include "Fruit.hpp"

namespace ms_pacman {

constexpr int DEFAULT_LIVES = 3;
constexpr int NORMAL_PELLET_POINTS = 10;
constexpr int POWER_PELLET_POINTS = 50;
constexpr int GHOST_POINTS = 200;

struct Score {
  int lives = DEFAULT_LIVES;
  int points = 0;
  int eatenPellets = 0;
  std::vector<GenericFruit> eatenFruits;

  void game_reset() {
    lives = DEFAULT_LIVES;
    points = 0;
    eatenFruits.clear();
  }

  void pellet_reset() {
    eatenPellets = 0;
  }

  void add(auto & ghost) {
    ghost.die();
    points += GHOST_POINTS;
  }

  void add(GenericFruit & fruit) {
    points += Fruits::eat(fruit);
    eatenFruits.emplace_back(fruit);
  }

  void add(const Pellet &) {
    eatenPellets++;
    points += NORMAL_PELLET_POINTS;
  }

  void add(const SuperPellet &) {
    eatenPellets++;
    points += POWER_PELLET_POINTS;
  }
};

} // namespace ms_pacman

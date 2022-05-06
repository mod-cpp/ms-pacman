#include "Level.hpp"
#include <catch2/catch.hpp>
#include <iostream>

static int countPellets(ms_pacman::array2d<int, 31, 28> array) {
  int pellets = 0;
  int super_pellets = 0;

  for (size_t i = 0; i < std::size(array); i++)
    for (size_t j = 0; j < std::size(array[i]); j++)
      if (array[i][j] == static_cast<int>(ms_pacman::Level::Cell::PELLET))
        pellets++;
      else if (array[i][j] == static_cast<int>(ms_pacman::Level::Cell::SUPER_PELLET))
        super_pellets++;

  return pellets + super_pellets;
}

TEST_CASE("Check num pellets") {
  for (ms_pacman::Level level : ms_pacman::levels) {
    int counted = countPellets(level.maze_data);
    REQUIRE(level.getNumPellets() == counted);
  }
}

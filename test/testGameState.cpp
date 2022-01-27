#include "AtlasFruits.hpp"
#include "GameState.hpp"
#include <tuple>
#include <catch2/catch.hpp>

TEST_CASE("Check initial state of GameState") {
  ms_pacman::GameState gameState;
  REQUIRE(std::tuple_size<decltype(gameState.ghosts)>::value == 4);
  REQUIRE(gameState.inputState.direction() == ms_pacman::Direction::NONE);
  REQUIRE(ms_pacman::Fruits::sprite(gameState.currentFruit) == ms_pacman::Atlas::fruit_cherry);
  REQUIRE(gameState.levelNum == 0);
  REQUIRE(gameState.level.num_pellets == 228);
  REQUIRE(gameState.score.lives == ms_pacman::DEFAULT_LIVES);
  REQUIRE(gameState.score.points == 0);
  REQUIRE(gameState.score.eatenPellets == 0);
  REQUIRE(gameState.score.eatenFruits.empty());
}

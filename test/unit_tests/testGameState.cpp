#include "AtlasFruits.hpp"
#include "GameState.hpp"
#include <catch2/catch.hpp>
#include <tuple>

TEST_CASE("Check initial state of GameState") {
  ms_pacman::GameState gameState;
  REQUIRE(std::tuple_size<decltype(gameState.ghosts)>::value == 4);
  REQUIRE(gameState.inputState.direction() == ms_pacman::Direction::NONE);
  REQUIRE(isSamePosition(ms_pacman::Fruits::sprite(gameState.currentFruit()), ms_pacman::Atlas::fruit_cherry));
  REQUIRE(gameState.levelNum == 0);
  REQUIRE(gameState.level.num_pellets == 228);
  REQUIRE(gameState.score.lives == ms_pacman::DEFAULT_LIVES);
  REQUIRE(gameState.score.points == 0);
  REQUIRE(gameState.score.eatenPellets == 0);
  REQUIRE(gameState.score.eatenFruits.empty());
}

static void simulatePlay(ms_pacman::GameState & state) {
  state.levelNum = 3;
  state.loadLevel();
  state.score.lives = 0;
  state.score.points = 1337;
  state.score.eatenPellets = 42;
  state.score.eatenFruits.emplace_back(state.currentFruit());
}

TEST_CASE("Restarting the game resets state") {
  ms_pacman::GameState gameState;
  simulatePlay(gameState);
  gameState.restartGame();
  REQUIRE(gameState.levelNum == 0);
  REQUIRE(gameState.level.num_pellets == 228);
  REQUIRE(gameState.score.lives == ms_pacman::DEFAULT_LIVES);
  REQUIRE(gameState.score.points == 0);
  REQUIRE(gameState.score.eatenPellets == 0);
  REQUIRE(gameState.score.eatenFruits.empty());
}
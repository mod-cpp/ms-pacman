#include "Fruit.hpp"
#include "GameState.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Fruit default initialization", "[fruits]") {
  ms_pacman::Cherry fruit;
  REQUIRE_FALSE(fruit.visible());
  REQUIRE(fruit.value == 100);
  REQUIRE(fruit.sprite.x == 0);
  REQUIRE(fruit.sprite.y == 6);
  REQUIRE(fruit.position().x == Approx(13.5));
  REQUIRE(fruit.position().y == Approx(17));
}

TEST_CASE("Fruit Visibility", "[fruits]") {
  ms_pacman::GameState gameState;
  REQUIRE_FALSE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));

  SECTION("9 seconds but no pellets eaten") {
    ms_pacman::DefaultBoard board;
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(9001), board, gameState.score.eatenPellets);
    REQUIRE_FALSE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));
  }

  SECTION("9 seconds and 70 pellets eaten") {
    // "Eat 70 pellets", do an update and check the state
    ms_pacman::DefaultBoard board;
    gameState.score.eatenPellets = 70;
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(1), board, gameState.score.eatenPellets);
    REQUIRE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));

    // Wait more than 9 seconds and then check the state again
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(9001), board, gameState.score.eatenPellets);
    REQUIRE_FALSE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));
  }

  SECTION("70 and 170 pellets eaten") {
    // "Eat 70 pellets", do an update and check the state
    ms_pacman::DefaultBoard board;
    gameState.score.eatenPellets = 70;
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(1), board, gameState.score.eatenPellets);
    REQUIRE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));

    // Wait more than 9 seconds and then check the state again
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(9001), board, gameState.score.eatenPellets);
    REQUIRE_FALSE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));

    // "Eat 170 pellets", do an update and check the state
    gameState.score.eatenPellets = 170;
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(1), board, gameState.score.eatenPellets);
    REQUIRE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));

    // Wait more than 9 seconds and then check the state again
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(9001), board, gameState.score.eatenPellets);
    REQUIRE_FALSE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));

    // We should never get a visible state again, since we only show 2 fruits
    gameState.score.eatenPellets = 1000;
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(1), board, gameState.score.eatenPellets);
    REQUIRE_FALSE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));

    // Wait more than 9 seconds and then check the state again
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(9001), board, gameState.score.eatenPellets);
    REQUIRE_FALSE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));
  }

  SECTION("Eating a fruit") {
    REQUIRE(ms_pacman::Fruits::eat(gameState.currentFruit()) == 0);

    ms_pacman::DefaultBoard board;
    gameState.score.eatenPellets = 70;
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(1), board, gameState.score.eatenPellets);
    REQUIRE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));
    REQUIRE(ms_pacman::Fruits::eat(gameState.currentFruit()) == ms_pacman::Fruits::value(gameState.currentFruit()));

    // Wait more than 9 seconds and then check the state again
    ms_pacman::Fruits::update(gameState.currentFruit(), std::chrono::milliseconds(9001), board, gameState.score.eatenPellets);
    REQUIRE_FALSE(ms_pacman::Fruits::isVisible(gameState.currentFruit()));
    REQUIRE(ms_pacman::Fruits::eat(gameState.currentFruit()) == 0);
  }
}
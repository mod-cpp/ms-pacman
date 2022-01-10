#include "Fruit.hpp"
#include "GameState.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Fruit default initialization", "[fruits]") {
  ms_pacman::Fruit<ms_pacman::FruitType::Cherry> fruit;
  REQUIRE_FALSE(fruit.isVisible());
  REQUIRE(fruit.value() == 100);
  REQUIRE(fruit.currentSprite().x == 0);
  REQUIRE(fruit.currentSprite().y == 6);
  REQUIRE(fruit.position().x == Approx(13.5));
  REQUIRE(fruit.position().y == Approx(17));
}

TEST_CASE("Fruit Visibility", "[fruits]") {
  ms_pacman::GameState gameState;
  REQUIRE_FALSE(gameState.currentFruit.isVisible());

  SECTION("9 seconds but no pellets eaten") {
    gameState.currentFruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.currentFruit.isVisible());
  }

  SECTION("9 seconds and 70 pellets eaten") {
    // "Eat 70 pellets", do an update and check the state
    gameState.score.eatenPellets = 70;
    gameState.currentFruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE(gameState.currentFruit.isVisible());

    // Wait more than 9 seconds and then check the state again
    gameState.currentFruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.currentFruit.isVisible());
  }

  SECTION("70 and 170 pellets eaten") {
    // "Eat 70 pellets", do an update and check the state
    gameState.score.eatenPellets = 70;
    gameState.currentFruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE(gameState.currentFruit.isVisible());

    // Wait more than 9 seconds and then check the state again
    gameState.currentFruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.currentFruit.isVisible());

    // "Eat 170 pellets", do an update and check the state
    gameState.score.eatenPellets = 170;
    gameState.currentFruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE(gameState.currentFruit.isVisible());

    // Wait more than 9 seconds and then check the state again
    gameState.currentFruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.currentFruit.isVisible());

    // We should never get a visible state again, since we only show 2 fruits
    gameState.score.eatenPellets = 1000;
    gameState.currentFruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.currentFruit.isVisible());

    // Wait more than 9 seconds and then check the state again
    gameState.currentFruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.currentFruit.isVisible());
  }

  SECTION("Eating a fruit") {
    REQUIRE(gameState.currentFruit.eat() == 0);

    gameState.score.eatenPellets = 70;
    gameState.currentFruit.update(std::chrono::milliseconds(1), gameState.score.eatenPellets);
    REQUIRE(gameState.currentFruit.isVisible());
    REQUIRE(gameState.currentFruit.eat() == gameState.currentFruit.value());

    // Wait more than 9 seconds and then check the state again
    gameState.currentFruit.update(std::chrono::milliseconds(9001), gameState.score.eatenPellets);
    REQUIRE_FALSE(gameState.currentFruit.isVisible());
    REQUIRE(gameState.currentFruit.eat() == 0);
  }
}
#include <catch2/catch.hpp>

#include "HighScore.hpp"
#include "HighScoreFile.hpp"

TEST_CASE("Empty HighScore has 0 top score", "[highscore]") {
  HighScore highScore;
  REQUIRE(highScore.top() == 0);
}

TEST_CASE("Load HighScore File", "[highscore]") {
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
}

TEST_CASE("Check HighScore File", "[highscore]") {
  HighScore highScore;
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
  auto parsed = highScore.parse(input);
  REQUIRE(parsed.size() == 2);
}

TEST_CASE("Populate Using HighScore File", "[highscore]") {
  HighScore highScore;
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
  auto parsed = highScore.parse(input);
  REQUIRE(parsed.size() == 2);
  highScore.populate(std::move(parsed));
  REQUIRE(highScore.top() == 20000);
  REQUIRE(highScore.num_players() == 2);
}

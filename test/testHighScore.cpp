#include <catch2/catch.hpp>

#include "HighScore.hpp"
#include "HighScoreFile.hpp"

TEST_CASE("Empty HighScore has 0 top score", "[highscore]") {
  ms_pacman::HighScore highScore{"empty_highscore.txt"};
  REQUIRE(highScore.top() == 0);
}

TEST_CASE("Load HighScore File", "[highscore]") {
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
}

TEST_CASE("Check HighScore File", "[highscore]") {
  ms_pacman::HighScore highScore{"highscore.txt"};
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
  auto parsed = highScore.parse(input);
  REQUIRE(parsed.size() == 4);
}

TEST_CASE("Populate Using HighScore File", "[highscore]") {
  ms_pacman::HighScore highScore{"highscore.txt"};
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
  auto parsed = highScore.parse(input);
  REQUIRE(parsed.size() == 4);
  highScore.populate(std::move(parsed));
  REQUIRE(highScore.top() == 2124);
  REQUIRE(highScore.num_players() == 4);
}

TEST_CASE("Transfer ownership of HighScore File", "[highscore]") {
  ms_pacman::HighScore highScore{"highscore.txt"};
  HighScoreFile file("highscore.txt");
  REQUIRE(file.is_valid());
  highScore.initialize(std::move(file));
  REQUIRE(!file.is_valid()); // NOLINT
}

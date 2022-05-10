#define CATCH_CONFIG_EXTERNAL_INTERFACES
#include <catch2/catch.hpp>

#include "HighScore.hpp"
#include "HighScoreFile.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>

struct HighScoreListener : Catch::TestEventListenerBase {

  using TestEventListenerBase::TestEventListenerBase; // inherit constructor

  void testCaseStarting(Catch::TestCaseInfo const &) override {
    // Perform some setup before a test case is run
    std::basic_ofstream<char> outputStream = std::ofstream("highscore.txt");
    outputStream << "Corentin,1345\n";
    outputStream << "Patricia,2124\n";
    outputStream << "Ólafur,1337\n";
  }

  void testCaseEnded(Catch::TestCaseStats const &) override {
    // Tear-down after a test case is run
    std::remove("highscore.txt");
    std::remove("empty_highscore.txt");
  }
};
CATCH_REGISTER_LISTENER(HighScoreListener)

TEST_CASE("Empty HighScore has no top score", "[highscore]") {
  ms_pacman::HighScore highScore{ "empty_highscore.txt" };
  const auto & top = highScore.top();
  REQUIRE(!top.has_value());
}

TEST_CASE("Load HighScore File", "[highscore]") {
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
}

TEST_CASE("Check HighScore File", "[highscore]") {
  ms_pacman::HighScore highScore{ "highscore.txt" };
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
  auto parsed = highScore.parse(input);
  REQUIRE(parsed.size() == 3);
}

TEST_CASE("Populate Using HighScore File", "[highscore]") {
  ms_pacman::HighScore highScore{ "highscore.txt" };
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
  auto parsed = highScore.parse(input);
  REQUIRE(parsed.size() == 3);
  highScore.populate(parsed);
  REQUIRE(highScore.num_players() == 3);
}

TEST_CASE("Transfer ownership of HighScore File", "[highscore]") {
  ms_pacman::HighScore highScore{ "highscore.txt" };
  HighScoreFile file("highscore.txt");
  REQUIRE(file.is_valid());
  highScore.initialize(std::move(file));
  REQUIRE(!file.is_valid()); // NOLINT
}

#define CATCH_CONFIG_EXTERNAL_INTERFACES
#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

#include "HighScore.hpp"
#include "HighScoreFile.hpp"
#include "StringView.hpp"

#include <fstream>
#include <iostream>

using namespace ms_pacman;

// 41. std::string_view and std::span
namespace exercises_41 {

TEST_CASE("Exercise 411 : Make whole word uppercase", "[.][41]") {
  CHECK("SIX" == StringView::to_upper("six"));
  CHECK("THINGS" == StringView::to_upper("things"));
  CHECK("BEFORE" == StringView::to_upper("before"));
  std::string haystack = "Why, sometimes I’ve believed as many as six impossible things before breakfast.";
  const std::string needle = "impossible";
  auto pos = haystack.find(needle);
  CHECK("IMPOSSIBLE" == StringView::to_upper({ haystack.data() + pos, needle.length() }));
}

TEST_CASE("Exercise 412 : Trim leading and trailing white space", "[.][41]") {
  CHECK("six" == StringView::trim("six"));
  CHECK("things" == StringView::trim(" things"));
  CHECK("before" == StringView::trim("before "));
  CHECK("impossible" == StringView::trim(" impossible "));
  CHECK("impossible things" == StringView::trim(" impossible things "));
}

TEST_CASE("Exercise 413 : Split view into tokens based on whitespace", "[.][41]") {
  std::string haystack = "Why, sometimes I've believed as many as six impossible things before breakfast.";
  const std::string delimiter = " ";
  std::vector<std::string> tokens = StringView::split(haystack);
  REQUIRE(tokens.size() == 12);
  if (tokens.size() == 12) {
    CHECK(tokens[0] == "Why,");
    CHECK(tokens[1] == "sometimes");
    CHECK(tokens[2] == "I've");
    CHECK(tokens[3] == "believed");
    CHECK(tokens[4] == "as");
    CHECK(tokens[5] == "many");
    CHECK(tokens[6] == "as");
    CHECK(tokens[7] == "six");
    CHECK(tokens[8] == "impossible");
    CHECK(tokens[9] == "things");
    CHECK(tokens[10] == "before");
    CHECK(tokens[11] == "breakfast.");
  }
}

TEST_CASE("Exercise 414 : Split view into tokens based on delimiter", "[.][41]") {
  std::string haystack = "Why,sometimes,I've,believed,as,many,as,six,impossible,things,before,breakfast.";
  const std::string delimiter = " ";
  std::vector<std::string> tokens = StringView::split(haystack, ',');
  REQUIRE(tokens.size() == 12);
  if (tokens.size() == 12) {
    CHECK(tokens[0] == "Why");
    CHECK(tokens[1] == "sometimes");
    CHECK(tokens[2] == "I've");
    CHECK(tokens[3] == "believed");
    CHECK(tokens[4] == "as");
    CHECK(tokens[5] == "many");
    CHECK(tokens[6] == "as");
    CHECK(tokens[7] == "six");
    CHECK(tokens[8] == "impossible");
    CHECK(tokens[9] == "things");
    CHECK(tokens[10] == "before");
    CHECK(tokens[11] == "breakfast.");
  }
}

TEST_CASE("Exercise 415 : Get int from string", "[.][41]") {
  CHECK(0 == StringView::to_int("0"));
  CHECK(42 == StringView::to_int("42"));
  CHECK(1337 == StringView::to_int("1337"));
  CHECK(1234 == StringView::to_int("1234"));
  CHECK(5678 == StringView::to_int("5678"));
}

// Catch 2 setup and teardown
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

TEST_CASE("Integration: Populate Using HighScore File", "[.][41]") {
  HighScore highScore{ "highscore.txt" };
  HighScoreFile file("highscore.txt");
  auto input = file.read_all();
  REQUIRE(!input.empty());
  auto parsed = highScore.parse(input);
  REQUIRE(parsed.size() == 3);
  CHECK(std::get<0>(parsed[0]) == "CORENTIN");
  CHECK(std::get<1>(parsed[0]) == 1345);
  CHECK(std::get<0>(parsed[1]) == "PATRICIA");
  CHECK(std::get<1>(parsed[1]) == 2124);
  CHECK(std::get<0>(parsed[2]) == "ÓLAFUR");
  CHECK(std::get<1>(parsed[2]) == 1337);
  highScore.populate(parsed);
  const std::optional<player> & top = highScore.top();
  REQUIRE(top.has_value());
  REQUIRE(top->score == 2124);
  REQUIRE(highScore.num_players() == 3);
}

} // namespace exercises_41

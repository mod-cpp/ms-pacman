#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

#include "StringView.hpp"

using namespace ms_pacman;

// 42. std::string_view and std::span
namespace exercises_42 {

constexpr void unused(auto X) {
  (void)X;
}

TEST_CASE("Exercise 421 : Make whole word uppercase", "[.][42]") {
  CHECK("SIX" == StringView::to_upper("six"));
  CHECK("THINGS" == StringView::to_upper("things"));
  CHECK("BEFORE" == StringView::to_upper("before"));
  std::string haystack = "Why, sometimes I’ve believed as many as six impossible things before breakfast.";
  const std::string needle = "impossible";
  auto pos = haystack.find(needle);
  CHECK("IMPOSSIBLE" == StringView::to_upper({ haystack.data() + pos, needle.length() }));
}

TEST_CASE("Exercise 422 : Trim leading and trailing white space", "[.][42]") {
  CHECK("six" == StringView::trim("six"));
  CHECK("things" == StringView::trim(" things"));
  CHECK("before" == StringView::trim("before "));
  CHECK("impossible" == StringView::trim(" impossible "));
  CHECK("impossible things" == StringView::trim(" impossible things "));
}

std::vector<std::string> split(std::string_view view) {
  unused(view);
  std::vector<std::string> tokens;
  // Split view into tokens based on whitespace
  return tokens;
}

TEST_CASE("Exercise 423 : Split view into tokens based on whitespace", "[.][42]") {
  std::string haystack = "Why, sometimes I’ve believed as many as six impossible things before breakfast.";
  const std::string delimiter = " ";
  std::vector<std::string> tokens = split(haystack);
  REQUIRE(tokens.size() == 12);
  if (tokens.size() == 12) {
    CHECK(tokens[0] == "Why,");
    CHECK(tokens[1] == "sometimes");
    CHECK(tokens[2] == "I’ve");
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

} // namespace exercises_42

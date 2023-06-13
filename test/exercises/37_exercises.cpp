#include <catch2/catch_all.hpp>

// To enable a test remove [.] from the tags on the test

#include <array>
#include <map>
#include <type_traits>

// 37. std::tuple and structured bindings
namespace exercises_37 {

// Comment out define below
#define ENABLE_TEST_371
TEST_CASE("Exercise 371 : structured binding of a std::array", "[.][37]") {
  // EXAMPLE
  {
    std::array ints = { 12, 23, 34, 45 };

    auto [a, b, c, d] = ints;

    static_assert(std::is_same_v<decltype(a), int>);
    CHECK(a == 12);
    CHECK(b == 23);
    CHECK(c == 34);
    CHECK(d == 45);
  }

#ifndef ENABLE_TEST_371
  std::array chars = { 'h', 'e', 'y' };

  // Use structured binding to get the characters in chars and put then in x,y,z

  // Use the checks below to test it
  static_assert(std::is_same_v<decltype(x), char>);
  CHECK(x == 'h');
  CHECK(y == 'e');
  CHECK(z == 'y');
#endif
}

// Comment out define below
#define ENABLE_TEST_372
TEST_CASE("Exercise 372 : structured binding of a struct", "[.][37]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  // EXAMPLE
  {
    Point p = { 42, 24 };

    auto [x, y] = p;

    static_assert(std::is_same_v<decltype(x), int>);
    CHECK(x == 42);
    CHECK(y == 24);
  }

#ifndef ENABLE_TEST_372
  Point q = { 12, 21 };

  // Use structured binding to get the ints in q and put then in xx and yy

  // Use the checks below to test it
  static_assert(std::is_same_v<decltype(xx), int>);
  CHECK(xx == 12);
  CHECK(yy == 21);
#endif
}

// Comment out define below
#define ENABLE_TEST_373
TEST_CASE("Exercise 373 : structured binding of a std::tuple", "[.][37]") {
  // EXAMPLE
  {
    std::tuple p = std::make_tuple(42, 24);

    auto [x, y] = p;

    static_assert(std::is_same_v<decltype(x), int>);
    CHECK(x == 42);
    CHECK(y == 24);
  }

#ifndef ENABLE_TEST_373
  std::tuple q = std::make_tuple(21, 12);

  // Use structured binding to get the ints in q and put then in xx and yy

  // Use the checks below to test it
  static_assert(std::is_same_v<decltype(xx), int>);
  CHECK(xx == 21);
  CHECK(yy == 12);
#endif
}

// Comment out define below
#define ENABLE_TEST_374
TEST_CASE("Exercise 374 : structured binding of a std::map", "[.][37]") {
  std::map<std::string, int> map{
    { "Corentin", 1345 },
    { "Patricia", 2124 },
    { "Olafur", 1337 }
  };

  // EXAMPLE
  {
    std::pair<std::string, int> high_score = std::make_pair("", 0);
    for (const auto & [name, score] : map) {
      static_assert(std::is_same_v<decltype(name), const std::string>);
      static_assert(std::is_same_v<decltype(score), const int>);

      if (score > high_score.second)
        high_score = { name, score };
    }

    CHECK(high_score.second == 2124);
    CHECK(high_score.first == "Patricia");
  }

#ifndef ENABLE_TEST_374
  // Use the loop and a low_score std::pair to find the lowest score
  for (const auto & [name, score] : map) {
    static_assert(std::is_same_v<decltype(name), const std::string>);
    static_assert(std::is_same_v<decltype(score), const int>);
    // Find lowest score
  }

  // Use the checks below to test it
  CHECK(low_score.second == 1337);
  CHECK(low_score.first == "Olafur");
#endif
}

} // namespace exercises_37

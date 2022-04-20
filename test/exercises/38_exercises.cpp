#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

// 38. Variadic templates, fold expressions and parameter packs
namespace exercises_38 {

// Note use of comma operator
constexpr void unused(auto ...X) {
  (..., (void)X);
}

constexpr bool any_of(auto ...item) {
  unused(item...);
  return false;
}

TEST_CASE("Exercise 381 : Implement any_of", "[.][38]") {
  REQUIRE(true == any_of(false, false, true));
  REQUIRE(false == any_of(false, false, false));
  REQUIRE(true == any_of(true));
  REQUIRE(false == any_of(false));
  REQUIRE(true == any_of(true, true, true));
}

constexpr bool all_of(auto ...item) {
  unused(item...);
  return false;
}

TEST_CASE("Exercise 382 : Implement all_of", "[.][38]") {
  REQUIRE(false == all_of(false, false, true));
  REQUIRE(false == all_of(false, false, false));
  REQUIRE(true == all_of(true));
  REQUIRE(false == all_of(false));
  REQUIRE(true == all_of(true, true, true));
}

} // namespace exercises_38

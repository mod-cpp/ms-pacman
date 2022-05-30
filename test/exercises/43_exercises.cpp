#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

// 43. Constexpr and Consteval
namespace exercises_43 {

// Comment out define below
#define ENABLE_TEST_431
TEST_CASE("Exercise 431 : Implement a consteval function that calculates the volume of a box", "[.][43]") {
#ifndef ENABLE_TEST_431
  static_assert(volume(1, 2, 3) == 6);
  static_assert(volume(2, 4, 8) == 64);
#endif
}

} // namespace exercises_43

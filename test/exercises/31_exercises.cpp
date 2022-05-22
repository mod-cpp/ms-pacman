#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

// 31. Introduction
namespace exercises_31 {

TEST_CASE("Exercise 31x : Make sure running exercise tests work", "[31]") {
  REQUIRE(true == true);
}

// HINT: To enable a test remove [.] from the tags on the test
TEST_CASE("Exercise 311 : Enable the test and make it green", "[.][31]") {
  REQUIRE(true == false);
}

// HINT: https://github.com/catchorg/Catch2/blob/v2.x/docs/assertions.md
TEST_CASE("Exercise 312 : Make both asserts run (distinguish between REQUIRE and CHECK in Catch2)", "[.][31]") {
  REQUIRE(true == false);
  CHECK(false == true);
}

} // namespace exercises_31

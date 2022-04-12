#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

// 31. Introduction
namespace exercises_31 {

// HINT: To enable a test remove [.] from the tags on the test
TEST_CASE("Exercise 311 : Enable a test and make it green", "[.][31]") {
  REQUIRE(true == false);
}

// HINT: https://github.com/catchorg/Catch2/blob/v2.x/docs/assertions.md
TEST_CASE("Exercise 312 : Distinguish between REQUIRE and CHECK in Catch2", "[.][31]") {
  CHECK(true == false);
  CHECK(false == true);
}

}; // namespace exercises_31

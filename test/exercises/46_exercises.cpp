#include <catch2/catch.hpp>

// 46. Pragmatic introduction to move semantics and return value optimizations

TEST_CASE("46 Demo", "[!shouldfail][46]") {
  REQUIRE(true == false);
}

#include <catch2/catch.hpp>

// 43. Constexpr and Consteval

TEST_CASE("43 Demo", "[!shouldfail][43]") {
  REQUIRE(true == false);
}

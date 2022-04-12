#include <catch2/catch.hpp>

// 47. Safety

TEST_CASE("47 Demo", "[!shouldfail][47]") {
  REQUIRE(true == false);
}

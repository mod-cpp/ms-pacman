#include <catch2/catch.hpp>

//#define RUN_TESTS

#ifdef RUN_TESTS
#define DISABLE ""
#else
#define DISABLE "[.]"
#endif

// 32. Overloading

TEST_CASE("32 Demo", DISABLE"[32]") {
  REQUIRE(true == false);
}

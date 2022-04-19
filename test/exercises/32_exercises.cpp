#include <catch2/catch.hpp>

#include <vector>

// To enable a test remove [.] from the tags on the test

// 32. Overloading
namespace exercises_32 {

enum class ReturnValue {
  First,
  Second,
  Third,
  Fourth,
  Wrong
};

ReturnValue doThing(int) {
  return ReturnValue::First;
}

ReturnValue doThing(bool) {
  return ReturnValue::Second;
}

ReturnValue doThing(std::vector<int>) {
  return ReturnValue::Third;
}

// Try to guess the right answer before testing it
TEST_CASE("Exercise 321 : Which overload will be called?", "[.][32]") {
  CHECK(doThing(42) == ReturnValue::Wrong);
  CHECK(doThing(true) == ReturnValue::Wrong);
  CHECK(doThing({ 1, 2 }) == ReturnValue::Wrong);
}

// Comment out define below
#define ENABLE_TEST_322
TEST_CASE("Exercise 322 : Make a new overload to make the 'doThing' call below un-ambiguous", "[.][32]") {
#ifndef ENABLE_TEST_322
  CHECK(doThing(42.0) == ReturnValue::Fourth);
#endif
}

} // namespace exercises_32

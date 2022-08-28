#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

#include "StringView.hpp"

using namespace ms_pacman;

// 42. C++ 20: Ranges
namespace exercises_42 {

TEST_CASE("Exercise 420 : Trim leading and trailing white space", "[.][42]") {
  CHECK("six" == StringView::trim("six"));
  CHECK("things" == StringView::trim(" things"));
  CHECK("before" == StringView::trim("before "));
  CHECK("impossible" == StringView::trim(" impossible "));
  CHECK("impossible things" == StringView::trim(" impossible things "));
}

} // namespace exercises_42

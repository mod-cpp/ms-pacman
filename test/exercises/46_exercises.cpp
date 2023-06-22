#include <catch2/catch_all.hpp>

// To enable a test remove [.] from the tags on the test

// 46. Pragmatic introduction to move semantics and return value optimizations
namespace exercises_46 {

constexpr void unused(auto X) {
  (void)X;
}

struct Point {
  int x = 0;
  int y = 0;
};

struct Size {
  size_t width = 0;
  size_t height = 0;
};

struct Rect {
  size_t width() const { return size.width; }
  size_t height() const { return size.height; }
  int x() const { return point.x; }
  int y() const { return point.y; }
  int right() const { return point.x + int(size.width); }
  int bottom() const { return point.y + int(size.height); }

  Point point;
  Size size;
};

static Rect bounding_box(const Rect & one, const Rect & two) {
  unused(one);
  unused(two);
  int x = 0;
  int y = 0;
  //  int right = 0;
  //  int bottom = 0;
  size_t width = 0;
  size_t height = 0;
  return { { x, y }, { width, height } };
}

TEST_CASE("Exercise 461 : Implement bounding_box", "[.][46]") {
  {
    Rect one = { { 1, 1 }, { 3, 2 } };
    Rect two = { { 3, 4 }, { 3, 3 } };
    Rect box = bounding_box(one, two);
    CHECK(box.x() == 1);
    CHECK(box.y() == 1);
    CHECK(box.width() == 5);
    CHECK(box.height() == 6);
  }
  {
    Rect one = { { 1, 1 }, { 3, 2 } };
    Rect two = { { 3, 4 }, { 3, 3 } };
    Rect box = bounding_box(two, one);
    CHECK(box.x() == 1);
    CHECK(box.y() == 1);
    CHECK(box.width() == 5);
    CHECK(box.height() == 6);
  }
}

// TODO Tests on move and RVO and NRVO

} // namespace exercises_46

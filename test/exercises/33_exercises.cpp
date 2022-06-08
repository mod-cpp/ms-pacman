#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

#include <compare>

// 33. Operators
namespace exercises_33 {

struct Point {
  int x = 0;
  int y = 0;
};

// Comment out define below
#define ENABLE_TEST_331
TEST_CASE("Exercise 331 : operator== as a free function", "[.][33]") {
  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_331
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_331
  CHECK(p != other);
#endif
}

// Comment out define below
#define ENABLE_TEST_332
TEST_CASE("Exercise 332 : operator== as a defaulted member function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_332
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_332
  CHECK(p != other);
#endif
}

// Comment out define below
#define ENABLE_TEST_333
TEST_CASE("Exercise 333 : operator== as a custom member function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_333
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_333
  CHECK(p != other);
#endif
}

// Comment out define below
#define ENABLE_TEST_334
TEST_CASE("Exercise 334 : operator<=> as a free function", "[.][33]") {
  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_334
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_334
  CHECK(p != other);
  CHECK(p <= other);
#endif
}

// Comment out define below
#define ENABLE_TEST_335
TEST_CASE("Exercise 335 : operator<=> as a defaulted member function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_335
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_335
  CHECK(p != other);
  CHECK(p <= other);
#endif
}

// Comment out define below
#define ENABLE_TEST_336
TEST_CASE("Exercise 336 : operator<=> as a custom member function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_336
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_336
  CHECK(p != other);
  CHECK(p <= other);
#endif
}

TEST_CASE("Exercise 337 : operator() as a custom member function", "[.][33]") {
  struct OrigoVisitor {
    constexpr auto operator()(const Point &) const { return false; }
  };

  OrigoVisitor visit;
  Point p;
  CHECK(visit(p));

  Point other{ 1, 1 };
  CHECK(!visit(other));
}

} // namespace exercises_33

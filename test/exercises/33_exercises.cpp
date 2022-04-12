#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

namespace exercises_33 {

// 33. Operators

TEST_CASE("Exercise 331 : operator== as a free function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
  // CHECK(p == p);

  Point other{ 1, 1 };
  CHECK(other.x == 0);
  // CHECK(p != other);
}

TEST_CASE("Exercise 332 : operator== as a defaulted member function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
  // CHECK(p == p);

  Point other{ 1, 1 };
  CHECK(other.x == 0);
  // CHECK(p != other);
}

TEST_CASE("Exercise 333 : operator== as a custom member function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
  // CHECK(p == p);

  Point other{ 1, 1 };
  CHECK(other.x == 0);
  // CHECK(p != other);
}

TEST_CASE("Exercise 334 : operator<=> as a free function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
  // CHECK(p == p);

  Point other{ 1, 1 };
  CHECK(other.x == 0);
  // CHECK(p != other);
  // CHECK(p <= other);
}

TEST_CASE("Exercise 335 : operator<=> as a defaulted member function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
  // CHECK(p == p);

  Point other{ 1, 1 };
  CHECK(other.x == 0);
  // CHECK(p != other);
  // CHECK(p <= other);
}

TEST_CASE("Exercise 336 : operator<=> as a custom member function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  Point p;
  CHECK(p.x == 0);
  // CHECK(p == p);

  Point other{ 1, 1 };
  CHECK(other.x == 0);
  // CHECK(p != other);
  // CHECK(p <= other);
}

TEST_CASE("Exercise 337 : operator() as a custom member function", "[.][33]") {
  struct Point {
    int x = 0;
    int y = 0;
  };

  struct OrigoVisitor {
    constexpr auto operator()(const Point &) const { return false; }
  };

  OrigoVisitor visit;
  Point p;
  CHECK(visit(p));

  Point other{ 1, 1 };
  CHECK(!visit(other));
}

}; // namespace exercises_33

#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

// 44. Concepts- Intermediate
namespace exercises_44 {

enum class color {
  blue,
  red,
  green,
  purple
};

enum class shape {
  triangle,
  square,
  circle
};

template<color C, shape S>
struct shape_t {
  static constexpr auto color = C;
  static constexpr auto shape = S;
};

template<color C>
struct circle : shape_t<C, shape::circle> {};

template<color C>
struct square : shape_t<C, shape::square> {};

template<color C>
struct triangle : shape_t<C, shape::triangle> {};

template<typename T>
concept is_shape = true;

template<typename T>
concept is_circle = (is_shape<T> && T::shape == shape::circle);

template<typename T>
concept is_red = (is_shape<T> && T::color == color::red);

template<typename T>
concept is_red_circle = is_circle<T> && is_red<T>;

enum class ReturnValue {
  First,
  Second,
  Third,
  Fourth,
  Wrong
};

ReturnValue process(is_shape auto) {
  return ReturnValue::First;
}

ReturnValue process(is_circle auto) {
  return ReturnValue::Second;
}

ReturnValue process(is_red auto) {
  return ReturnValue::Third;
}

ReturnValue process(is_red_circle auto) {
  return ReturnValue::Fourth;
}

TEST_CASE("Exercise 441 : Reason about conjunction", "[.][44]") {
  {
    auto red_circle = circle<color::red>{};
    CHECK(process(red_circle) == ReturnValue::Wrong);
  }
  {
    auto green_circle = circle<color::green>{};
    CHECK(process(green_circle) == ReturnValue::Wrong);
  }
  {
    auto blue_circle = circle<color::blue>{};
    CHECK(process(blue_circle) == ReturnValue::Wrong);
  }
  {
    auto red_square = square<color::red>{};
    CHECK(process(red_square) == ReturnValue::Wrong);
  }
  {
    auto purple_square = square<color::purple>{};
    CHECK(process(purple_square) == ReturnValue::Wrong);
  }
  {
    auto red_triangle = triangle<color::red>{};
    CHECK(process(red_triangle) == ReturnValue::Wrong);
  }
  {
    auto blue_triangle = triangle<color::blue>{};
    CHECK(process(blue_triangle) == ReturnValue::Wrong);
  }
}

} // namespace exercises_44

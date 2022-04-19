#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

#include <variant>

// 36. std::variant and std::visit
namespace exercises_36 {

constexpr int Wrong = 1337;

constexpr void unused(auto X) {
  (void)X;
}

// Copied from: https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

struct circle {};
struct triangle {};
struct square {};

using shape = std::variant<circle, triangle, square>;

static int sides(const shape & count_shape) {
  unused(Wrong);
  return std::visit(overloaded{
                      [](const circle &) { return Wrong; },
                      [](const triangle &) { return Wrong; },
                      [](const square &) { return Wrong; },
                    },
                    count_shape);
  ;
}

TEST_CASE("Exercise 361 : Fill in std::visit", "[.][36]") {
  shape var = circle{};
  CHECK(sides(var) == 1);
  var = square{};
  CHECK(sides(var) == 4);
  var = triangle{};
  CHECK(sides(var) == 3);
}

} // namespace exercises_36

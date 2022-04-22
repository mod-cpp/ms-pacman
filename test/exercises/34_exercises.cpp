#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

#include <numeric>

// 34. Class templates, function templates, non-type parameters
namespace exercises_34 {

constexpr void unused(auto X) {
  (void)X;
}

template<typename T>
class set {
public:
  std::size_t size() const {
    return items.size();
  }

  bool contains(const T & item) const {
    return std::any_of(items.begin(), items.end(), [&item](T current) { return current == item; });
  }

  void operator<<(const T & item) {
    unused(item);
    // Exercise 341
    // Hint: https://en.cppreference.com/w/cpp/container/vector/push_back
  }

private:
  std::vector<T> items;
};

// Only add items not already in the set
TEST_CASE("Exercise 341 : Implement streaming operator as insert into the set", "[.][34]") {
  set<int> int_set;
  CHECK(int_set.size() == 0);
  int_set << 42;
  CHECK(int_set.size() == 1);
  int_set << 43;
  CHECK(int_set.size() == 2);
  int_set << 42;
  CHECK(int_set.size() == 2);
  int_set << 43;
  CHECK(int_set.size() == 2);
}

template<typename T>
static T accumulate(std::vector<T> vec, T init) {
  unused(vec);
  // Exercise 342
  // Hint: https://en.cppreference.com/w/cpp/algorithm/accumulate
  return init;
}

TEST_CASE("Exercise 342 : Implement a function template", "[.][34]") {
  std::vector<int> int_vec = { 21, 32, 43, 54 };
  CHECK(accumulate(int_vec, 0) == (21 + 32 + 43 + 54));

  std::vector<std::string> string_vec = { "21", "32", "43", "54" };
  CHECK(accumulate(string_vec, { "" }) == "21324354");
}

static auto acc(const auto & vec, const auto & init) {
  unused(vec);
  // Exercise 343
  // Hint: https://en.cppreference.com/w/cpp/algorithm/accumulate
  return init;
}

TEST_CASE("Exercise 343 : Implement an abbreviated function template", "[.][34]") {
  std::vector<int> int_vec = { 21, 32, 43, 54 };
  CHECK(acc(int_vec, 0) == (21 + 32 + 43 + 54));

  std::vector<std::string> string_vec = { "21", "32", "43", "54" };
  std::string init = "";
  CHECK(acc(string_vec, init) == "21324354");
}

} // namespace exercises_34

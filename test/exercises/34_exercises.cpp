#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

namespace exercises_34 {
constexpr void unused(auto X) {
  (void)X;
}

// 34. Class templates, function templates, non-type parameters

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
  ;
  int_set << 43;
  CHECK(int_set.size() == 2);
}
}; // namespace exercises_34

#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

// 35. Aliases and alias templates
namespace exercises_35 {

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
    if (!contains(item))
      items.push_back(item);
  }

private:
  std::vector<T> items;
};

TEST_CASE("Exercise 351 : using alias int_set", "[.][35]") {
  //  int_set set;
  //  CHECK(set.size() == 0);
  //  set << 4;
  //  CHECK(set.size() == 1);
  //  set << 4;
  //  CHECK(set.size() == 1);
}

}; // namespace exercises_35

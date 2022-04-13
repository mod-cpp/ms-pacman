#include <catch2/catch.hpp>

// To enable a test remove [.] from the tags on the test

#include <array>

// 35. Aliases and alias templates
namespace exercises_35 {

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

const std::size_t ROWS = 31;
const std::size_t COLUMNS = 28;

//template <typename T, auto Width, auto Height>
//using array2d = <IMPLEMENT ME>;

//template <typename T>
//using grid = array2d<T, COLUMNS, ROWS>;

// Exercise 352: Implement array2d
// Hint: https://en.cppreference.com/w/cpp/container/array
TEST_CASE("Exercise 352 : Implement array2d (alias template)", "[.][35]") {
  unused(ROWS);
  unused(COLUMNS);
//  grid<int> board;
//  CHECK(board.size() == ROWS);
//  CHECK(board[0].size() == COLUMNS);
}

} // namespace exercises_35

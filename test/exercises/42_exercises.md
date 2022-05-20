[< Back](README.md)

# 42. C++ 20: Ranges

* [Exercise 420](#exercise-420)

## [Exercise 420][1]

### Trim leading and trailing white space in StringView.hpp

* [std::string_view][2]

```cpp
std::string trim(std::string_view /*view*/) {
  // Exercise 420 : Trim leading and trailing white space
  return {};
}
```

<details>
   <summary>Solution</summary>

```cpp
#include <ranges>
inline std::string trim(std::string_view view) {
  auto start_it = std::ranges::find_if_not(view, ::isspace);
  auto end_it = std::ranges::find_if_not(std::ranges::reverse_view(view), ::isspace);
  return std::string{ start_it, end_it.base() };
}
```

</details>

[1]: 42_exercises.cpp

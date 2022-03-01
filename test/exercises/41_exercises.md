[< Back](README.md)

# 41. C++ 20: Ranges

* [Exercise 410](#exercise-410)

## [Exercise 410][1]

### Trim leading and trailing white space in StringView.hpp

* [std::string_view][2]

```cpp
std::string trim(std::string_view /*view*/) {
  // Exercise 410 : Trim leading and trailing white space
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

[1]: 41_exercises.cpp

[< Back](README.md)

# 35. Aliases and alias templates

* [Exercise 350](#exercise-350)
* [Exercise 351](#exercise-351)
* [Exercise 352](#exercise-352)

## Exercise 350

Make an alias called EatingAnimations for std::array<GridPosition, 4> in the code below.

```cpp
constexpr std::array<GridPosition, 4> down_animation{ pacman_down_wide, pacman_down_narrow, pacman_down_closed, pacman_down_narrow };
constexpr std::array<GridPosition, 4> left_animation{ pacman_left_wide, pacman_left_narrow, pacman_left_closed, pacman_left_narrow };
constexpr std::array<GridPosition, 4> right_animation{ pacman_right_wide, pacman_right_narrow, pacman_right_closed, pacman_right_narrow };
constexpr std::array<GridPosition, 4> up_animation{ pacman_up_wide, pacman_up_narrow, pacman_up_closed, pacman_up_narrow };
constexpr std::array<GridPosition, 4> death_animation{ pacman_left_narrow, pacman_up_narrow, pacman_right_narrow, pacman_down_narrow };
```


<details>
   <summary>Solution</summary>

```cpp
using EatingAnimations = std::array<GridPosition, 4>;
constexpr EatingAnimations down_animation{ pacman_down_wide, pacman_down_narrow, pacman_down_closed, pacman_down_narrow };
constexpr EatingAnimations left_animation{ pacman_left_wide, pacman_left_narrow, pacman_left_closed, pacman_left_narrow };
constexpr EatingAnimations right_animation{ pacman_right_wide, pacman_right_narrow, pacman_right_closed, pacman_right_narrow };
constexpr EatingAnimations up_animation{ pacman_up_wide, pacman_up_narrow, pacman_up_closed, pacman_up_narrow };
constexpr EatingAnimations death_animation{ pacman_left_narrow, pacman_up_narrow, pacman_right_narrow, pacman_down_narrow };
```
</details>

## [Exercise 351][1]
### using alias int_set

* cppreference : [Type alias, alias template][3]

<details>
   <summary>Solution</summary>

```cpp
using int_set = set<int>;
```
</details>

## [Exercise 352][1]
### Implement array2d (alias template)

* cppreference : [std::array][2]
* cppreference : [Type alias, alias template][3]

<details>
   <summary>Solution</summary>

```cpp
template<typename T, auto Width, auto Height>
using array2d = std::array<std::array<T, Width>, Height>;
```
</details>

[1]: 35_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/container/array
[3]: https://en.cppreference.com/w/cpp/language/type_alias

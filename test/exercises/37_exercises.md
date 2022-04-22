[< Back](README.md)

# 37. std::tuple and structured bindings

* [Exercise 370](#exercise-370)
* [Exercise 371](#exercise-371)
* [Exercise 372](#exercise-372)
* [Exercise 373](#exercise-373)
* [Exercise 374](#exercise-374)
* [Exercise 375](#exercise-375)

## Exercise 370

Use a structured binding to "unpack" the animation parameter and extract out the posistion into a 
variable called pos. What should we do with the other member?

```cpp
constexpr GridPosition animationFrame(const MsPacManAnimation & animation, Direction direction) {
  switch (direction) {
    case Direction::LEFT:
      return left_animation[animation.position];
    case Direction::RIGHT:
      return right_animation[animation.position];
    case Direction::UP:
      return up_animation[animation.position];
    case Direction::DOWN:
      return down_animation[animation.position];
    case Direction::NONE:
    default:
      return Atlas::pacman_left_narrow;
  }
}
```

<details>
   <summary>Solution</summary>

```cpp
constexpr GridPosition animationFrame(const MsPacManAnimation & animation, Direction direction) {
  const auto & [pos, _] = animation;
  switch (direction) {
    case Direction::LEFT:
      return left_animation[pos];
    case Direction::RIGHT:
      return right_animation[pos];
    case Direction::UP:
      return up_animation[pos];
    case Direction::DOWN:
      return down_animation[pos];
    case Direction::NONE:
    default:
      return Atlas::pacman_left_narrow;
  }
}
```
</details>

## [Exercise 371][1]
### structured binding of a C array

* cppreference : [Structured Binding Declaration][2]

<details>
   <summary>Solution</summary>

```cpp
  auto [x, y, z] = chars;
```
</details>

## [Exercise 372][1]
### structured binding of a std::array

* cppreference : [Structured Binding Declaration][2]

<details>
   <summary>Solution</summary>

```cpp
  auto [x, y, z] = chars;
```
</details>

## [Exercise 373][1]
### structured binding of a struct

* cppreference : [Structured Binding Declaration][2]

<details>
   <summary>Solution</summary>

```cpp
  auto [xx, yy] = q;
```
</details>

## [Exercise 374][1]
### structured binding of a std::tuple

* cppreference : [Structured Binding Declaration][2]

<details>
   <summary>Solution</summary>

```cpp
  auto [xx, yy] = q;
```
</details>

## [Exercise 375][1]
### structured binding of a std::map

* cppreference : [Structured Binding Declaration][2]
* cppreference : [std::pair][3]
* cppreference : [std::make_pair][4]
* cppreference : [std::numeric_limits\<T\>::max][5]
* cppreference : [std::numeric_limits\<T\>::min][6]
* cppreference : [std::map][7]
* cppreference : [std::is_same_v][8]
* cppreference : [decltype][9]
* cppreference : [static_assert][10]

<details>
   <summary>Solution</summary>

```cpp
  std::pair<std::string, int> low_score = std::make_pair("", std::numeric_limits<int>::max());
  for (const auto & [name, score] : map) {
    static_assert(std::is_same_v<decltype(name), const std::string>);
    static_assert(std::is_same_v<decltype(score), const int>);
    // Find lowest score
    if (score < low_score.second)
      low_score = { name, score };
  }
```
</details>

[1]: 37_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/language/structured_binding
[3]: https://en.cppreference.com/w/cpp/utility/pair
[4]: https://en.cppreference.com/w/cpp/utility/pair/make_pair
[5]: https://en.cppreference.com/w/cpp/types/numeric_limits/max
[6]: https://en.cppreference.com/w/cpp/types/numeric_limits/min
[7]: https://en.cppreference.com/w/cpp/container/map
[8]: https://en.cppreference.com/w/cpp/types/is_same
[9]: https://en.cppreference.com/w/cpp/language/decltype
[10]: https://en.cppreference.com/w/cpp/language/static_assert

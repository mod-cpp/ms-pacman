[< Back](README.md)

# 37. std::tuple and structured bindings

## Exercise 370

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

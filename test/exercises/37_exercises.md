[< Back](README.md)

# 37. std::tuple and structured bindings

## Exercise 370: 

## [Exercise 371][1] : structured binding of a C array

<details>
   <summary>Solution</summary>

```cpp
  auto [x, y, z] = chars;
```
</details>

## [Exercise 372][1] : structured binding of a std::array

<details>
   <summary>Solution</summary>

```cpp
  auto [x, y, z] = chars;
```
</details>

## [Exercise 373][1] : structured binding of a struct

<details>
   <summary>Solution</summary>

```cpp
  auto [xx, yy] = q;
```
</details>

## [Exercise 374][1] : structured binding of a std::tuple

<details>
   <summary>Solution</summary>

```cpp
  auto [xx, yy] = q;
```
</details>

## [Exercise 375][1] : structured binding of a std::map

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

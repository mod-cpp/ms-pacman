[< Back](README.md)

# 38. Variadic templates, fold expressions and parameter packs

* [Exercise 380](#exercise-380)
* [Exercise 381](#exercise-381)
* [Exercise 382](#exercise-382)

## Exercise 380

## [Exercise 381][1]
### Implement any_of

<details>
   <summary>Solution</summary>

```cpp
constexpr bool any_of(auto ...item) {
  return (item || ...);
}
```
</details>

## [Exercise 382][1]
### Implement all_of

<details>
   <summary>Solution</summary>

```cpp
constexpr bool all_of(auto ...item) {
  return (item && ...);
}
```
</details>

[1]: 38_exercises.cpp

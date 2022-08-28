[< Back](README.md)

# 34. Class templates, function templates, non-type parameters

* [Exercise 340](#exercise-340)
* [Exercise 341](#exercise-341)
* [Exercise 342](#exercise-342)
* [Exercise 343](#exercise-343)

## Exercise 340

Rewrite the operator== to templates and use template specialization for the one with double

```cpp
constexpr bool operator==(const GridPosition & a, const GridPosition & b) {
  return a.x == b.x && a.y == b.y;
}

constexpr bool operator==(const Position & a, const Position & b) {
  constexpr double epsilon = std::numeric_limits<double>::epsilon();
  return std::abs(a.x - b.x) <= epsilon &&
         std::abs(a.y - b.y) <= epsilon;
}
```

<details>
   <summary>Solution</summary>

```cpp
template<typename T>
constexpr bool operator==(const BasicPosition<T> & a, const BasicPosition<T> & b) {
  return a.x == b.x && a.y == b.y;
}

template<>
inline bool operator==(const BasicPosition<double> & a, const BasicPosition<double> & b) {
  constexpr double epsilon = std::numeric_limits<double>::epsilon();
  return std::abs(a.x - b.x) <= epsilon &&
         std::abs(a.y - b.y) <= epsilon;
}
```
</details>

Extra time: replace all calls to isSamePosition with == and !=

## [Exercise 341][1]
### Implement streaming operator as insert into the set

* cppreference: [std::vector\<T\>::push_back][2]

<details>
   <summary>Solution</summary>

```cpp
  void operator<<(const T & item) {
    if (!contains(item))
      items.push_back(item);
  }
```
</details>

## [Exercise 342][1]
### Implement a function template

* cppreference: [std::accumulate][3]

<details>
   <summary>Solution</summary>

```cpp
template<typename T>
static T accumulate(std::vector<T> vec, T init) {
  return std::accumulate(vec.begin(), vec.end(), init);
}
```
</details>

## [Exercise 343][1]
### Implement an abbreviated function template

* cppreference: [std::accumulate][3]

Considering exercise 342 and 343 - how are they different? Will they match the same signatures?

<details>
   <summary>Solution</summary>

```cpp
static auto acc(const auto & vec, const auto & init) {
  return std::accumulate(vec.begin(), vec.end(), init);
}
```
</details>

[1]: 34_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/container/vector/push_back
[3]: https://en.cppreference.com/w/cpp/algorithm/accumulate

[< Back](README.md)

# 36. std::variant and std::visit

* [Exercise 360](#exercise-360)
* [Exercise 361](#exercise-361)

## Exercise 360

Rewrite teleport to use std::visit and overloaded instead.

```cpp
constexpr GridPosition teleport(const DefaultBoard & board, GridPosition position) {
  BoardCell cell = cellAtPosition(board, position);
  if (std::holds_alternative<Portal>(cell)) {
    return std::get<Portal>(cell).target_position;
  }
  return position;
}
```

<details>
   <summary>Solution</summary>

```cpp
constexpr GridPosition teleport(const DefaultBoard & board, GridPosition position) {
  BoardCell cell = cellAtPosition(board, position);
  return std::visit(overloaded{
                              [&](const Portal & p) { return p.target_position; },
                              [&position](const auto &) { return position;}
                              }, cell);
}
```
</details>


## [Exercise 361][1]
### Fill in std::visit

* cppreference: [std::variant][3]
* cppreference: [std::visit][2]

<details>
   <summary>Solution</summary>

```cpp
static int sides(const shape & count_shape) {
  unused(Wrong);
  return std::visit(overloaded{
                      [](const circle &) { return 1; },
                      [](const triangle &) { return 3; },
                      [](const square &) { return 4; },
                    },
                    count_shape);
  ;
}
```
</details>

[1]: 36_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/utility/variant/visit
[3]: https://en.cppreference.com/w/cpp/utility/variant

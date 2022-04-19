[< Back](README.md)

# 36. std::variant and std::visit

## Exercise 360: 

## [Exercise 361][1] : Fill in std::visit

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

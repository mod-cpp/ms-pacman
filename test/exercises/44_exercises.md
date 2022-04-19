[< Back](README.md)

# 44. Concepts

## Exercise 440:

## [Exercise 441][1] : Reason about conjunction

<details>
   <summary>Solution</summary>

```cpp
TEST_CASE("Exercise 441 : Reason about conjunction", "[44]") {
  {
    auto red_circle = circle<color::red>{};
    CHECK(process(red_circle) == ReturnValue::Fourth);
  }
  {
    auto green_circle = circle<color::green>{};
    CHECK(process(green_circle) == ReturnValue::Second);
  }
  {
    auto blue_circle = circle<color::blue>{};
    CHECK(process(blue_circle) == ReturnValue::Second);
  }
  {
    auto red_square = square<color::red>{};
    CHECK(process(red_square) == ReturnValue::Third);
  }
  {
    auto purple_square = square<color::purple>{};
    CHECK(process(purple_square) == ReturnValue::First);
  }
  {
    auto red_triangle = triangle<color::red>{};
    CHECK(process(red_triangle) == ReturnValue::Third);
  }
  {
    auto blue_triangle = triangle<color::blue>{};
    CHECK(process(blue_triangle) == ReturnValue::First);
  }
}
```
</details>

[1]: 44_exercises.cpp

[< Back](README.md)

# 46. Pragmatic introduction to move semantics and return value optimizations

## Exercise 460: 

## [Exercise 461][1] : Implement bounding_box

* cppreference : [std::min][2]
* cppreference : [std::max][3]

<details>
   <summary>Solution</summary>

```cpp
static Rect bounding_box(const Rect & one, const Rect & two) {
  int x = std::min(one.x(), two.x());
  int y = std::min(one.y(), two.y());
  int right = std::max(one.right(), two.right());
  int bottom = std::max(one.bottom(), two.bottom());
  auto width = static_cast<size_t>(right - x);
  auto height = static_cast<size_t>(bottom - y);
  return { { x, y }, { width, height } };
}
```

</details>

[1]: 46_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/algorithm/min
[3]: https://en.cppreference.com/w/cpp/algorithm/max

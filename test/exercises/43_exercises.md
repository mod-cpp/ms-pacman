[< Back](README.md)

# 43. constexpr and consteval

* [Exercise 430](#exercise-430)
* [Exercise 431](#exercise-431)

## Exercise 430
### Look at maze-builder

* Browse the code in the [repo][2]

## [Exercise 431][1]
### Implement a consteval function that calculates the volume of a box

<details>
   <summary>Solution</summary>

```cpp
consteval int volume(int width, int height, int depth) {
  return width * height * depth;
}
```
</details>

[1]: 43_exercises.cpp
[2]: https://github.com/mod-cpp/maze-builder

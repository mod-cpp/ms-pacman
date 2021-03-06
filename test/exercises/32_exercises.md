[< Back](README.md)

# 32. Overloading

* [Exercise 320](#exercise-320)
* [Exercise 321](#exercise-321)
* [Exercise 322](#exercise-322)

## Exercise 320 

Re-name all the functions called in GameState::step in [GameState.cpp][2] to step so
that they are all overloads.

```cpp
void GameState::step(std::chrono::milliseconds delta) {
  if (!stepMsPacMan(delta, msPacMan))
    return;

  stepGhosts(delta, ghosts);
  stepPellets(board);
  stepFruit(delta, currentFruit);
}
```

## [Exercise 321][1]
### Which overload will be called?

<details>
   <summary>Solution</summary>

```cpp
TEST_CASE("Exercise 321 : Which overload will be called?", "[32]") {
  CHECK(doThing(42) == ReturnValue::First);
  CHECK(doThing(true) == ReturnValue::Second);
  CHECK(doThing({ 1, 2 }) == ReturnValue::Third);
}
```
</details>

## [Exercise 322][1]
### Make a new overload to make the 'doThing' call below un-ambiguous

<details>
   <summary>Solution</summary>

```cpp
ReturnValue doThing(double) {
  return ReturnValue::Fourth;
}

//#define ENABLE_TEST_322
TEST_CASE("Exercise 322 : Make a new overload to make the 'doThing' call below un-ambiguous", "[32]") {
#ifndef ENABLE_TEST_322
  CHECK(doThing(42.0) == ReturnValue::Fourth);
#endif
}
```
</details>

[1]: 32_exercises.cpp
[2]: ../../lib/GameState.cpp

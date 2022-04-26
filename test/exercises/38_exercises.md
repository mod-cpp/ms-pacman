[< Back](README.md)

# 38. Variadic templates, fold expressions and parameter packs

* [Exercise 380](#exercise-380)
* [Exercise 381](#exercise-381)
* [Exercise 382](#exercise-382)

## [Exercise 380][1]
### Implement any_of

<details>
   <summary>Solution</summary>

```cpp
constexpr bool any_of(auto ...item) {
  return (item || ...);
}
```
</details>

## [Exercise 381][1]
### Implement all_of

<details>
   <summary>Solution</summary>

```cpp
constexpr bool all_of(auto ...item) {
  return (item && ...);
}
```
</details>

## Exercise 382

There is a lot of code repetition in GameState::stepGhosts

```cpp
void GameState::stepGhosts(const std::chrono::milliseconds & delta, Ghosts & ghost_tuple) {
  auto step_ghost = [&](auto & ghost) {
    ghost.update(delta, board);
    ghost.setTarget(board, msPacMan, std::get<Blinky>(ghost_tuple).positionInGrid());
  };

  std::apply([&step_ghost](Blinky &blinky, Pinky &pinky, Inky& inky, Clyde & clyde) {
    step_ghost(blinky);
    step_ghost(pinky);
    step_ghost(inky);
    step_ghost(clyde);
  }, ghost_tuple);

  std::apply([this](Blinky &blinky, Pinky &pinky, Inky& inky, Clyde & clyde) {
    checkCollision(blinky);
    checkCollision(pinky);
    checkCollision(inky);
    checkCollision(clyde);
  }, ghost_tuple);
}
```

Can you use a fold expression to reduce the amount of repetition?
Which fold expression?

Simplify the code

<details>
   <summary>Solution</summary>

```cpp
void GameState::stepGhosts(const std::chrono::milliseconds & delta, Ghosts & ghost_tuple) {
  auto step_ghost = [&](auto & ghost) {
    ghost.update(delta, board);
    ghost.setTarget(board, msPacMan, std::get<Blinky>(ghost_tuple).positionInGrid());
  };

  std::apply([&step_ghost](auto... & ghost) {
    (step_ghost(ghost), ...);
  }, ghost_tuple);

  std::apply([this](auto... & ghost) {
    (checkCollision(ghost), ...);
  }, ghost_tuple);
}
```
</details>

[1]: 38_exercises.cpp

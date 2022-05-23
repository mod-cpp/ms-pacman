[< Back](README.md)

# 38. Variadic templates, fold expressions and parameter packs

* [Exercise 380](#exercise-380)
* [Exercise 381](#exercise-381)
* [Exercise 382](#exercise-382)

## Exercise 380

There is a lot of code repetition in GameState::stepGhosts

```cpp
void GameState::stepGhosts(const std::chrono::milliseconds & delta, Ghosts & ghost_tuple) {
  auto step_ghost = [&](auto & ghost) {
    ghost.update(delta, board);
    ghost.setTarget(board, msPacMan, std::get<Blinky>(ghost_tuple).positionInGrid());
  };

  auto step_all_ghosts = [&step_ghost](Blinky & blinky, Pinky & pinky, Inky & inky, Sue & sue) {
    step_ghost(blinky);
    step_ghost(pinky);
    step_ghost(inky);
    step_ghost(sue);
  };

  std::apply(step_all_ghosts, ghost_tuple);

  auto check_collision_all_ghosts = [this](Blinky & blinky, Pinky & pinky, Inky & inky, Sue & sue) {
    checkCollision(blinky);
    checkCollision(pinky);
    checkCollision(inky);
    checkCollision(sue);
  };

  std::apply(check_collision_all_ghosts, ghost_tuple);
}
```

Can you use a fold expression to reduce the amount of repetition?
Which fold expression?

<details>
   <summary>Solution</summary>

```cpp
void GameState::stepGhosts(const std::chrono::milliseconds & delta, Ghosts & ghost_tuple) {
  auto step_ghost = [&](auto & ghost) {
    ghost.update(delta, board);
    ghost.setTarget(board, msPacMan, std::get<Blinky>(ghost_tuple).positionInGrid());
  };

  auto step_all_ghosts = [&step_ghost](auto & ...ghost) {
    (step_ghost(ghost), ...);
  };

  std::apply(step_all_ghosts, ghost_tuple);

  auto check_collision_all_ghosts = [this](auto & ...ghost) {
    (checkCollision(ghost), ...);
  };

  std::apply(check_collision_all_ghosts, ghost_tuple);
}
```
</details>

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

[< Back](README.md)

# Extra : Exercise-X3

## Make the fruits move

<details>
   <summary>Hint 1: How to get NPC behavior</summary>
Make Fruit inherit from NPC.
</details>

<details>
   <summary>Hint 2: Implement the inheritance</summary>

```cpp
  Fruit() : NPC(Atlas::fruit_target_pos, true) {}

  double speed() const override {
    return 0.75;
  }

  bool isWalkable(const DefaultBoard & board, GridPosition /*current_position*/, GridPosition target_position) const override {
    return isWalkableForFruit(board, target_position);
  }
```
</details>

<details>
   <summary>Hint 3: Movement rules</summary>

```cpp
constexpr bool isWalkableForFruit(const DefaultBoard & board, GridPosition point) {
  BoardCell cell = cellAtPosition(board, point);
  return std::visit(overloaded{
                      [](const Wall &) { return false; },
                      [](const Pen &) { return false; },
                      [](const PenDoor &) { return false; },
                      [](const auto &) {
                        return true;
                      } },
                    cell);
}
```
</details>

<details>
   <summary>Hint 4: Add call to update position</summary>

```cpp
  void update(std::chrono::milliseconds time_delta, const DefaultBoard & board, int eatenPellets) {
    // ...

    if (visible()) {
      updatePosition(time_delta, board);
    }
  }
```
</details>

<details>
   <summary>Hint 5: Store the initial start position</summary>

```cpp
  void setStartPosition(Position position) {
    start_position = position;
    setPosition(start_position);
  }
```
</details>

<details>
   <summary>Hint 6: Update the initial start position</summary>

```cpp
void GameState::reset() {
  // ...
  Fruits::setStartPosition(currentFruit(), gridPositionToPosition(fruitPortal));
}

void GameState::choseFruitPortal() {
  // ...
  Fruits::setStartPosition(currentFruit(), gridPositionToPosition(fruitPortal));
}
```
</details>

<details>
   <summary>Hint 7: Update start position for second fruit round</summary>

```cpp
  void hide() {
    // ...
    setPosition(start_position);
  }
```
</details>

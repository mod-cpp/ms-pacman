[< Back](README.md)

# Extra : Exercise-X1

## Ms-Pac-Man should go faster when she eats a super pellet

<details>
   <summary>Hint 1: What to look at for inspiration</summary>

Look at how the SUPER_SPEED cheat works
</details>

<details>
   <summary>Hint 2: Members needed</summary>

```cpp
  double scale_speed = 1.0;
  DeltaTimer timer{ std::chrono::seconds(5) };
  bool hasSuperSpeed() const { return scale_speed > 1.0; }
```
</details>

<details>
   <summary>Hint 3: Where to update the speed</summary>

```cpp
  const double position_delta = cheat_speed * scale_speed * 0.004 * double(time_delta.count());
```
</details>

<details>
   <summary>Hint 4: How to start it</summary>

```cpp
void MsPacMan::eat(const SuperPellet &) {
  // TODO Exercise-X1 : Ms-Pac-Man should go faster when she eats a super pellet
  scale_speed = 2.0;
}
```
</details>

<details>
   <summary>Hint 5: How to count down</summary>

```cpp
  if (hasSuperSpeed()) {
    timer.inc(time_delta);
    if (timer.timed_out()) {
      scale_speed = 1.0;
      timer.reset();
    }
  }
```
</details>

<details>
   <summary>Hint 6: How to reset</summary>

```cpp
void MsPacMan::reset() {
  // ...
  scale_speed = 1.0;
  timer.reset();
}
```
</details>

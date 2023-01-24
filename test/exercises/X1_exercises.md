[< Back](README.md)

# Extra : Exercise-X1

## Ms-Pac-Man should go faster when she eats a super pellet

<details>
   <summary>Hint 1: What to look at for inspiration</summary>

Look at how the SUPER_SPEED cheat works in [Cheats.hpp][1]
</details>

<details>
   <summary>Hint 2: Members needed</summary>

In [MsPacMan.hpp][2]
```cpp
  double scale_speed = 1.0;
  DeltaTimer timer{ std::chrono::seconds(5) };
  bool hasSuperSpeed() const { return scale_speed > 1.0; }
```
</details>

<details>
   <summary>Hint 3: Where to update the speed</summary>

In `MsPacMan::updateMazePosition` in [MsPacMan.cpp][3]
```cpp
  const double position_delta = cheat_speed * scale_speed * 0.004 * double(time_delta.count());
```
</details>

<details>
   <summary>Hint 4: How to start it</summary>

In [MsPacMan.cpp][3]
```cpp
void MsPacMan::eat(const SuperPellet &) {
  // TODO Exercise-X1 : Ms-Pac-Man should go faster when she eats a super pellet
  scale_speed = 2.0;
}
```
</details>

<details>
   <summary>Hint 5: How to count down</summary>

In [MsPacMan.cpp][3]
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

In [MsPacMan.cpp][3]
```cpp
void MsPacMan::reset() {
  // ...
  scale_speed = 1.0;
  timer.reset();
}
```
</details>

[1]: ../../lib/include/Cheats.hpp
[2]: ../../lib/include/MsPacMan.hpp
[3]: ../../lib/MsPacMan.cpp

[< Back](README.md)

# Extra : Exercise-X2

## Make a cheat code (C-A-T) that gives you 9 lives

<details>
   <summary>Hint 1: What to look at for inspiration</summary>

Look at how the SUPER_SPEED cheat works
</details>

<details>
   <summary>Hint 2: Where to add it</summary>

```cpp
enum class Cheat {
  SuperSpeed,
  NineLives
};
```
</details>

<details>
   <summary>Hint 3: How to define it</summary>

```cpp
constexpr CheatCode NINE_LIVES = {{ Code::C, Code::A, Code::T }};
```
</details>

<details>
   <summary>Hint 4: How to handle it</summary>

```cpp
      else if (cheat_code == NINE_LIVES)
        cheat = Cheat::NineLives;
```
</details>

<details>
   <summary>Hint 5: How to implement it</summary>

```cpp
      case Cheat::NineLives:
        gameState.score.lives = 9;
        break;
```
</details>

<details>
   <summary>Hint 6: How to test it</summary>

```cpp
TEST_CASE("Happy Day: NineLives", "[cheats]") {
  Cheats cheats;
  auto first = cheats.add_cheat(Code::C);
  CHECK(!first);
  auto second = cheats.add_cheat(Code::A);
  CHECK(!second);
  auto third = cheats.add_cheat(Code::T);
  REQUIRE(third.has_value());
  CHECK(third.value() == Cheat::NineLives);
}
```
</details>

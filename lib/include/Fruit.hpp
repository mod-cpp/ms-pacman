#pragma once

#include "Atlas.hpp"
#include "Position.hpp"
#include <chrono>
#include <variant>

namespace ms_pacman {

enum class FruitType {
  Cherry,
  Strawberry,
  Orange,
  Pretzel,
  Apple,
  Pear,
  Banana
};

struct GameState;

template<FruitType Type>
class Fruit {
public:
  void update(std::chrono::milliseconds time_delta, int eatenPellets) {
    if (visible) {
      time_visible += time_delta;
    }

    if (time_visible > std::chrono::seconds(9)) {
      hide();
    } else if ((index == 0 && eatenPellets >= 70) || (index == 1 && eatenPellets >= 170)) {
      // We show the fruit twice, once at 70 pellets and once at 170
      visible = true;
    }
  }

  constexpr GridPosition currentSprite() const {
    constexpr auto ret = []() {
      switch (Type) {
        case FruitType::Cherry: return Atlas::fruit_cherry;
        case FruitType::Strawberry: return Atlas::fruit_strawberry;
        case FruitType::Orange: return Atlas::fruit_orange;
        case FruitType::Pretzel: return Atlas::fruit_pretzel;
        case FruitType::Apple: return Atlas::fruit_apple;
        case FruitType::Pear: return Atlas::fruit_pear;
        case FruitType::Banana: return Atlas::fruit_banana;
      }
    }();
    return ret;
  }

  constexpr Position position() const {
    // under the pen
    return { 13.5, 17 };
  }

  bool isVisible() const {
    return visible;
  }

  constexpr int value() const {
    constexpr auto ret = []() {
      switch (Type) {
        case FruitType::Cherry: return 100;
        case FruitType::Strawberry: return 200;
        case FruitType::Orange: return 500;
        case FruitType::Pretzel: return 700;
        case FruitType::Apple: return 1000;
        case FruitType::Pear: return 2000;
        case FruitType::Banana: return 5000;
      }
    }();
    return ret;
  }

  int eat() {
    if (!isVisible()) {
      return 0;
    }

    hide();
    return value();
  }

private:
  bool visible = false;
  int index = 0;
  std::chrono::milliseconds time_visible{ 0 };

  void hide() {
    index++;
    time_visible = std::chrono::seconds{ 0 };
    visible = false;
  }
};

using GenericFruit = std::variant<
  Fruit<FruitType::Cherry>,
  Fruit<FruitType::Strawberry>,
  Fruit<FruitType::Orange>,
  Fruit<FruitType::Pretzel>,
  Fruit<FruitType::Apple>,
  Fruit<FruitType::Pear>,
  Fruit<FruitType::Banana>>;

namespace Fruits {
constexpr void update(GenericFruit & currentFruit, std::chrono::milliseconds time_delta, int eatenPellets) {
  std::visit([&](auto && fruit) { fruit.update(time_delta, eatenPellets); }, currentFruit);
}

constexpr GridPosition currentSprite(const GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.currentSprite(); }, currentFruit);
}

constexpr int value(const GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.value(); }, currentFruit);
}

constexpr Position position(const GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.position(); }, currentFruit);
}

constexpr bool isVisible(const GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.isVisible(); }, currentFruit);
}

constexpr int eat(GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.eat(); }, currentFruit);
}
} // namespace Fruits

} // namespace ms_pacman

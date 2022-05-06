#pragma once

#include "AtlasFruits.hpp"
#include "Position.hpp"
#include <chrono>
#include <variant>

namespace ms_pacman {

template<typename Type>
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

  constexpr Position position() const { return Atlas::fruit_start; }

  bool isVisible() const {
    return visible;
  }

  int eat() {
    if (!isVisible()) {
      return 0;
    }

    hide();
    return Type::value;
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

struct Cherry : public Fruit<Cherry> {
  static constexpr GridPosition sprite = Atlas::fruit_cherry;
  static constexpr int value = 100;
};

struct Strawberry : public Fruit<Strawberry> {
  static constexpr GridPosition sprite = Atlas::fruit_strawberry;
  static constexpr int value = 200;
};

struct Orange : public Fruit<Orange> {
  static constexpr GridPosition sprite = Atlas::fruit_orange;
  static constexpr int value = 500;
};

struct Pretzel : public Fruit<Pretzel> {
  static constexpr GridPosition sprite = Atlas::fruit_pretzel;
  static constexpr int value = 700;
};

struct Apple : public Fruit<Apple> {
  static constexpr GridPosition sprite = Atlas::fruit_apple;
  static constexpr int value = 1000;
};

struct Pear : public Fruit<Pear> {
  static constexpr GridPosition sprite = Atlas::fruit_pear;
  static constexpr int value = 2000;
};

struct Banana : public Fruit<Banana> {
  static constexpr GridPosition sprite = Atlas::fruit_banana;
  static constexpr int value = 5000;
};

using GenericFruit = std::variant<Cherry, Strawberry, Orange, Pretzel, Apple, Pear, Banana>;

namespace Fruits {
constexpr void update(GenericFruit & currentFruit, std::chrono::milliseconds time_delta, int eatenPellets) {
  std::visit([&](auto && fruit) { fruit.update(time_delta, eatenPellets); }, currentFruit);
}

constexpr GridPosition sprite(const GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.sprite; }, currentFruit);
}

constexpr int value(const GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.value; }, currentFruit);
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

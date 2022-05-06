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
    if (visible()) {
      time_visible += time_delta;
    }

    if (time_visible > limit) {
      hide();
    } else if (Type::shouldShow(eatenPellets, index)) {
      show();
    }
  }

  int eat() {
    if (visible()) {
      hide();
      return Type::value;
    }
    return 0;
  }

  constexpr Position position() const { return Atlas::fruit_start; }
  bool visible() const { return is_visible; }

private:
  bool is_visible = false;
  int index = 0;
  std::chrono::milliseconds time_visible{ 0 };
  static constexpr auto limit = std::chrono::seconds(9);

  void show() {
    is_visible = true;
  }

  void hide() {
    index++;
    time_visible = std::chrono::seconds{ 0 };
    is_visible = false;
  }
};

struct Cherry : public Fruit<Cherry> {
  static constexpr GridPosition sprite = Atlas::fruit_cherry;
  static constexpr int value = 100;
  static constexpr bool shouldShow(int eatenPellets, int index) {
    // We show the Cherry twice, once at 70 pellets and once at 170
    return (index == 0 && eatenPellets >= 70) || (index == 1 && eatenPellets >= 170);
  }
};

struct Strawberry : public Fruit<Strawberry> {
  static constexpr GridPosition sprite = Atlas::fruit_strawberry;
  static constexpr int value = 200;
  static constexpr bool shouldShow(int eatenPellets, int) {
    return eatenPellets >= 70;
  }
};

struct Orange : public Fruit<Orange> {
  static constexpr GridPosition sprite = Atlas::fruit_orange;
  static constexpr int value = 500;
  static constexpr bool shouldShow(int eatenPellets, int) {
    return eatenPellets >= 70;
  }
};

struct Pretzel : public Fruit<Pretzel> {
  static constexpr GridPosition sprite = Atlas::fruit_pretzel;
  static constexpr int value = 700;
  static constexpr bool shouldShow(int eatenPellets, int) {
    return eatenPellets >= 70;
  }
};

struct Apple : public Fruit<Apple> {
  static constexpr GridPosition sprite = Atlas::fruit_apple;
  static constexpr int value = 1000;
  static constexpr bool shouldShow(int eatenPellets, int) {
    return eatenPellets >= 70;
  }
};

struct Pear : public Fruit<Pear> {
  static constexpr GridPosition sprite = Atlas::fruit_pear;
  static constexpr int value = 2000;
  static constexpr bool shouldShow(int eatenPellets, int) {
    return eatenPellets >= 70;
  }
};

struct Banana : public Fruit<Banana> {
  static constexpr GridPosition sprite = Atlas::fruit_banana;
  static constexpr int value = 5000;
  static constexpr bool shouldShow(int eatenPellets, int) {
    return eatenPellets >= 70;
  }
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
  return std::visit([](auto && fruit) { return fruit.visible(); }, currentFruit);
}

constexpr int eat(GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.eat(); }, currentFruit);
}
} // namespace Fruits

} // namespace ms_pacman

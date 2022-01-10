#pragma once

#include "Atlas.hpp"
#include "Position.hpp"
#include <chrono>
#include <variant>

namespace ms_pacman {

enum class FruitType {
  Cherry,
  Strawberry
};

struct GameState;

template <FruitType Type>
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
    constexpr auto ret = [](){
      switch (Type) {
        case FruitType::Cherry: return Atlas::fruit_cherry;
        case FruitType::Strawberry: return Atlas::fruit_strawberry;
      }
      return GridPosition{};
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
    // The cherry is worth 100
    return 100;
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
  }};

using GenericFruit = std::variant<Fruit<FruitType::Cherry>, Fruit<FruitType::Strawberry>>;

constexpr Position getFruitPosition(const GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.position(); }, currentFruit);
}

constexpr GridPosition getFruitGridPosition(const GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return positionToGridPosition(fruit.position()); }, currentFruit);
}

constexpr bool getFruitVisibility(const GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.isVisible(); }, currentFruit);
}

constexpr int eatFruits(GenericFruit & currentFruit) {
  return std::visit([](auto && fruit) { return fruit.eat(); }, currentFruit);
}

} // namespace pacman

#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <vector>

namespace ms_pacman {

class Cheats {
public:
  void add_cheat(sf::Keyboard::Key /*key*/) {}
  void use_cheat() {}

private:
  std::vector<sf::Keyboard::Key> keys;
};

} // namespace ms_pacman
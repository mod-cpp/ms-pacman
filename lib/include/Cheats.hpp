#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <vector>

namespace ms_pacman {

enum class Cheat {
  SuperSpeed
};

class Cheats {
public:
  std::optional<Cheat> add_cheat(sf::Keyboard::Key /*key*/) { return {}; }

private:
  std::vector<sf::Keyboard::Key> keys;
};

} // namespace ms_pacman
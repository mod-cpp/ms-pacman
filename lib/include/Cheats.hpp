#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <deque>

namespace ms_pacman {

enum class Cheat {
  SuperSpeed
};

using Code = sf::Keyboard::Key;

class Cheats {
public:
  std::optional<Cheat> add_cheat(Code key) {
    keys.push_back(key);
    if (keys.size() == 3) {
      if (keys[0] == Code::F && keys[1] == Code::O && keys[2] == Code::X) {
        keys.clear();
        return Cheat::SuperSpeed;
      } else {
        keys.pop_front();
      }
    }
    return {};
  }

private:
  std::deque<Code> keys;
};

} // namespace ms_pacman
#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <array>
#include <deque>
#include <optional>

namespace ms_pacman {

enum class Cheat {
  SuperSpeed
};

using Code = sf::Keyboard::Key;

struct CheatCode : std::array<Code, 3> {
  static constexpr auto length = 3;
};

constexpr CheatCode SUPER_SPEED = { { Code::F, Code::O, Code::X } };

class Cheats {
public:
  std::optional<Cheat> add_cheat(Code key) {
    std::optional<Cheat> cheat;

    keys.push_back(key);

    if (keys.size() == CheatCode::length) {
      auto cheat_code = CheatCode{ { keys[0], keys[1], keys[2] } };

      if (cheat_code == SUPER_SPEED)
        cheat = Cheat::SuperSpeed;

      // TODO Exercise-X2 : Make a cheat code that gives you infinite lives

      if (cheat)
        keys.clear();
      else
        keys.pop_front();
    }

    return cheat;
  }

private:
  std::deque<Code> keys;
};

} // namespace ms_pacman
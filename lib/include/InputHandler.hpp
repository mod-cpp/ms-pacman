#pragma once

#include <SFML/Window/Event.hpp>
#include <optional>

#include "Cheats.hpp"
#include "InputState.hpp"

namespace ms_pacman {

class InputHandler {
public:
  std::optional<Cheat> process(InputState & inputState, const sf::Event & event);

private:
  Cheats cheats;
};

} // namespace ms_pacman

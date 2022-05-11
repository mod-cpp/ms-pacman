#include "InputHandler.hpp"

namespace ms_pacman {

std::optional<Cheat> InputHandler::process(InputState & inputState, const sf::Event & event) {
  auto key_code = event.key.code;
  auto key_type = event.type;

  auto isKeyPressed = [&key_code, &key_type](sf::Keyboard::Key key) {
    return (key_type == sf::Event::KeyPressed) && (key_code == key);
  };

  switch (key_type) {
    case sf::Event::Closed:
      inputState.close = true;
      break;
    case sf::Event::KeyReleased:
    case sf::Event::KeyPressed:
      switch (key_code) {
        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
        case sf::Keyboard::Up:
        case sf::Keyboard::Down:
          inputState.down = isKeyPressed(sf::Keyboard::Key::Down);
          inputState.up = isKeyPressed(sf::Keyboard::Key::Up);
          inputState.left = isKeyPressed(sf::Keyboard::Key::Left);
          inputState.right = isKeyPressed(sf::Keyboard::Key::Right);
          break;
        default:
          if (key_type == sf::Event::KeyPressed)
            return cheats.add_cheat(key_code);
      }
      break;
    default: break;
  }
  return {};
}

} // namespace ms_pacman

#include "Game.hpp"
#include "GameState.hpp"
#include <chrono>

namespace ms_pacman {

void Game::run() {
  loadLevel();

  const std::chrono::milliseconds delta_time(1000 / 60);
  std::chrono::milliseconds accumulator(0);
  auto current_time = std::chrono::system_clock::now();

  while (true) {

    if (gameState.isLevelCompleted()) {
      gameState.increaseLevel();
      loadLevel();
    } else if (gameState.isGameOver()) {
      gameState.restartGame();
      loadLevel();
    }

    const auto newTime = std::chrono::system_clock::now();
    const auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - current_time);

    current_time = newTime;
    accumulator += frameTime;

    processEvents(gameState.inputState);
    if (gameState.inputState.close)
      return;

    while (accumulator >= delta_time) {
      gameState.step(delta_time);
      accumulator -= delta_time;
    }

    canvas.render(gameState);
  }
}

void Game::loadLevel() {
  const Level & level = gameState.level;
  canvas.loadMaze(level.background);
  gameState.board = level.create_board();
}

void Game::processEvents(InputState & inputState) {
  const auto event = canvas.pollEvent();

  if (!event)
    return;

  auto key_code = event.value().key.code;
  auto key_type = event.value().type;

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
          cheats.add_cheat(key_code);
          cheats.use_cheat();
      }
      break;
    default: break;
  }
}

} // namespace ms_pacman

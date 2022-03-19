#include "Game.hpp"
#include "GameState.hpp"
#include "HighScore.hpp"
#include "User.hpp"
#include <chrono>

namespace ms_pacman {

void Game::run() {
  loadLevel();

  const std::chrono::milliseconds delta_time(1000 / 60);
  std::chrono::milliseconds accumulator(0);
  auto current_time = std::chrono::system_clock::now();
  int highScore = loadBestScore();

  while (true) {

    if (gameState.isLevelCompleted()) {
      gameState.increaseLevel();
      loadLevel();
    } else if (gameState.isGameOver()) {
      highScore = std::max(highScore, gameState.score.points);
      saveScore(gameState.score.points);
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

    canvas.render(gameState, highScore);
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

  if (event.value().type == sf::Event::Closed) {
    inputState.close = true;
    return;
  }

  if (!(event.value().type == sf::Event::KeyPressed ||
        event.value().type == sf::Event::KeyReleased))
    return;

  auto isKeyPressed = [&](sf::Keyboard::Key k) {
    bool pressed = event.value().type == sf::Event::KeyPressed;
    return k == event.value().key.code && pressed;
  };

  inputState.down = isKeyPressed(sf::Keyboard::Key::Down);
  inputState.up = isKeyPressed(sf::Keyboard::Key::Up);
  inputState.left = isKeyPressed(sf::Keyboard::Key::Left);
  inputState.right = isKeyPressed(sf::Keyboard::Key::Right);
}

static HighScoreFile loadHighScoreFile() {
  return HighScoreFile("highscore.txt");
}

int Game::loadBestScore() const {
  HighScore scores;
  scores.initialize(loadHighScoreFile());
  return scores.top();
}

void Game::saveScore(int score) const {
  if (gameState.score.points == 0)
    return;
  HighScore scores;
  scores.initialize(loadHighScoreFile());
  scores.insert(userlogin(), score);
  scores.save("highscore.txt");
}

Game::~Game() {
  saveScore(gameState.score.points);
}

} // namespace ms_pacman

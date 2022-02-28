#include "GameState.hpp"

namespace ms_pacman {

constexpr int NORMAL_PELLET_POINTS = 10;
constexpr int POWER_PELLET_POINTS = 50;

void GameState::setGameOver() {
  game_over = true;
}

bool GameState::isGameOver() const {
  return game_over;
}

void GameState::restartGame() {
  levelNum = 0;
  loadLevel();
  game_over = false;
}

bool GameState::isLevelCompleted() const {
  return score.eatenPellets == level.getNumPellets();
}

void GameState::increaseLevel() {
  levelNum++;
  loadLevel();
}

void GameState::loadLevel() {
  if (levelNum == 0) {
    score.lives = DEFAULT_LIVES;
    score.points = 0;
    score.eatenFruits.clear();
  }
  level = getLevel(levelNum);
  score.eatenPellets = 0;
  reset();
}

void GameState::step(std::chrono::milliseconds delta) {

  if (isMsPacManDying()) {
    handleDeathAnimation(delta);
    return;
  }

  msPacMan.update(delta, inputState.direction(), board);

  if (!msPacMan.hasDirection())
    return;

  std::apply(
    [ this, &delta ]<typename... Ghost>(Ghost & ... ghost_param) {
      ([&]<typename T>(T & ghost) {
        ghost.update(delta, board);
        ghost.setTarget(board, msPacMan, std::get<Blinky>(ghosts).positionInGrid());
      }(ghost_param),
       ...);
    },
    ghosts);

  std::visit([&](auto && fruit) { fruit.update(delta, score.eatenPellets); }, currentFruit);

  std::apply([this](auto &... ghost) {
    (checkCollision(ghost), ...);
  },
             ghosts);

  eatPellets();
  eatFruit();
}

void GameState::handleDeathAnimation(std::chrono::milliseconds delta) {
  timeSinceDeath += delta;
  if (score.lives == 0 && timeSinceDeath.count() > 4000) {
    setGameOver();
  } else if (score.lives != 0 && timeSinceDeath.count() > 1000) {
    reset();
  }
}

void GameState::reset() {
  std::apply(
    [](auto &... ghost) {
      (ghost.reset(), ...);
    },
    ghosts);

  msPacMan.reset();
  timeSinceDeath = std::chrono::milliseconds(0);
}

void GameState::eatPellets() {
  const auto pos = msPacMan.positionInGrid();
  const auto & cell = cellAtPosition(board, pos);
  bool eaten = std::visit(overloaded{
                            [&](const Pellet &) {
                              score.eatenPellets++;
                              score.points += NORMAL_PELLET_POINTS;
                              return true;
                            },
                            [&](const SuperPellet &) {
                              score.eatenPellets++;
                              score.points += POWER_PELLET_POINTS;
                              std::apply([](auto &... ghost) { (ghost.frighten(), ...); },
                                         ghosts);
                              return true;
                            },
                            [](const auto &) {
                              return false;
                            },
                          },
                          cell);
  if (eaten)
    board[pos.y][pos.x] = Walkable{};
}

void GameState::eatFruit() {
  const auto pos = msPacMan.positionInGrid();
  const auto fruitpos = positionToGridPosition(Fruits::position(currentFruit));

  // TODO: hitboxes based collision
  if (Fruits::isVisible(currentFruit) && pos == fruitpos) {
    score.points += Fruits::eat(currentFruit);
    score.eatenFruits.emplace_back(currentFruit);
  }
}

void GameState::killMsPacMan() {
  msPacMan.die();
  score.lives--;
  timeSinceDeath = std::chrono::milliseconds(1);
}

bool GameState::isMsPacManDying() const {
  return timeSinceDeath.count() != 0;
}

} // namespace ms_pacman

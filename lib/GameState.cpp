#include "GameState.hpp"

namespace ms_pacman {

constexpr int NORMAL_PELLET_POINTS = 10;
constexpr int POWER_PELLET_POINTS = 50;

GameState::~GameState() {
  highScore.saveScore(score.points);
}

void GameState::setGameOver() {
  game_over = true;
}

bool GameState::isGameOver() const {
  return game_over;
}

void GameState::restartGame() {
  levelNum = 0;
  highScore.saveScore(score.points);
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
  if (!stepMsPacMan(delta, msPacMan))
    return;

  stepGhosts(delta, ghosts);
  stepPellets(board);
  stepFruit(delta, currentFruit);
}

bool GameState::stepMsPacMan(std::chrono::milliseconds & delta, MsPacMan & ms_pac_man) {
  // Life over, only render death animation
  if (isMsPacManDying()) {
    handleDeathAnimation(delta);
    return false;
  }

  ms_pac_man.update(delta, inputState.direction(), board);

  // Wait for Ms Pac-Man to move before starting the game
  return msPacMan.hasDirection();
}

void GameState::stepGhosts(const std::chrono::milliseconds & delta, Ghosts & ghost_tuple) {
  auto step_ghost = [&](auto & ghost) {
    ghost.update(delta, board);
    ghost.setTarget(board, msPacMan, std::__1::get<Blinky>(ghost_tuple).positionInGrid());
  };

  std::apply([&step_ghost](auto &... ghost) {
    (step_ghost(ghost), ...);
  },
             ghost_tuple);

  std::apply([this](auto &... ghost) {
    (checkCollision(ghost), ...);
  },
             ghost_tuple);
}

void GameState::stepPellets(DefaultBoard & grid) {
  const auto pos = msPacMan.positionInGrid();
  const auto & cell = cellAtPosition(grid, pos);
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
    grid[pos.y][pos.x] = Walkable{};
}

void GameState::stepFruit(std::chrono::milliseconds delta, GenericFruit & fruit) {
  const auto pos = msPacMan.positionInGrid();
  const auto fruitpos = positionToGridPosition(Fruits::position(fruit));

  // TODO: hitboxes based collision
  if (Fruits::isVisible(fruit) && isSamePosition(pos, fruitpos)) {
    score.points += Fruits::eat(fruit);
    score.eatenFruits.emplace_back(fruit);
  }

  std::visit([&](auto && fruit) { fruit.update(delta, score.eatenPellets); }, fruit);
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

void GameState::killMsPacMan() {
  msPacMan.die();
  score.lives--;
  timeSinceDeath = std::chrono::milliseconds(1);
}

bool GameState::isMsPacManDying() const {
  return timeSinceDeath.count() != 0;
}

} // namespace ms_pacman

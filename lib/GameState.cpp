#include "GameState.hpp"

namespace ms_pacman {

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
    score.game_reset();
  }
  level = getLevel(levelNum);
  score.pellet_reset();
  reset();
}

void GameState::step(std::chrono::milliseconds delta) {
  if (!stepMsPacMan(delta, msPacMan))
    return;

  stepGhosts(delta, ghosts);
  stepPellets(board);
  stepFruit(delta, currentFruit());
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
    ghost.setTarget(board, msPacMan, std::get<Blinky>(ghost_tuple).positionInGrid());
  };

  auto step_all_ghosts = [&step_ghost](Blinky & blinky, Pinky & pinky, Inky & inky, Sue & sue) {
    step_ghost(blinky);
    step_ghost(pinky);
    step_ghost(inky);
    step_ghost(sue);
  };

  std::apply(step_all_ghosts, ghost_tuple);

  auto check_collision_all_ghosts = [this](Blinky & blinky, Pinky & pinky, Inky & inky, Sue & sue) {
    checkCollision(blinky);
    checkCollision(pinky);
    checkCollision(inky);
    checkCollision(sue);
  };

  std::apply(check_collision_all_ghosts, ghost_tuple);
}

void GameState::stepPellets(DefaultBoard & grid) {
  const auto pos = msPacMan.positionInGrid();
  const auto & cell = cellAtPosition(grid, pos);
  bool eaten = std::visit(overloaded{
                            [&](const Pellet & pellet) {
                              score.add(pellet);
                              return true;
                            },
                            [&](const SuperPellet & superPellet) {
                              msPacMan.eat(superPellet);
                              score.add(superPellet);
                              auto frighten_ghosts = [](auto &... ghost) { (ghost.frighten(), ...); };
                              std::apply(frighten_ghosts, ghosts);
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

  if (Fruits::isVisible(fruit) && isSamePosition(pos, fruitpos)) {
    score.add(fruit);
  }

  std::visit([&](auto && fruit) { fruit.update(delta, board, score.eatenPellets); }, fruit);
}

void GameState::handleDeathAnimation(std::chrono::milliseconds delta) {
  timerSinceDeath.inc(delta);
  if (score.lives == 0 && timerSinceDeath.above(std::chrono::milliseconds(4000))) {
    setGameOver();
  } else if (score.lives != 0 && timerSinceDeath.above(std::chrono::milliseconds(1000))) {
    reset();
  }
}

void GameState::reset() {
  auto reset_ghosts = [](auto &... ghost) { (ghost.reset(), ...); };
  std::apply(reset_ghosts, ghosts);
  msPacMan.reset();
  timerSinceDeath.reset();
  Fruits::setStartPosition(currentFruit(), Atlas::fruit_target_pos);
}

void GameState::killMsPacMan() {
  msPacMan.die();
  score.lives--;
  timerSinceDeath.reset();
  timerSinceDeath.inc(std::chrono::milliseconds(1));
}

bool GameState::isMsPacManDying() const {
  return timerSinceDeath.above(std::chrono::milliseconds(0));
}

void GameState::loadBoard(std::tuple<DefaultBoard, Portals> loaded) {
  std::tie(board, portals) = loaded;
  choseFruitPortal();
}

void GameState::choseFruitPortal() {
  for (const auto & p : portals)
    if (p)
      fruitPortal = p.value();
  Fruits::setStartPosition(currentFruit(), Atlas::fruit_target_pos);
}

} // namespace ms_pacman

#include "GameState.hpp"

namespace ms_pacman {

constexpr int GHOST_POINTS = 200;
constexpr int NORMAL_PELLET_POINTS = 10;
constexpr int POWER_PELLET_POINTS = 50;

void GameState::step(std::chrono::milliseconds delta) {
  pacMan.update(delta, inputState.direction());

  if (isPacManDying()) {
    handleDeathAnimation(delta);
    return;
  }

  if (!pacMan.hasDirection())
    return;

  std::apply(
    [ this, &delta ]<typename... Ghost>(Ghost & ... ghost) {
      ([&]<typename T>(T & ghost) {
        ghost.update(delta);
        if constexpr (std::is_same_v<T, Blinky>) {
          ghost.setTarget(pacMan.position());
        }
        if constexpr (std::is_same_v<T, Pinky>) {
          ghost.setTarget(pacMan.positionInGrid(), pacMan.currentDirection());
        }
        if constexpr (std::is_same_v<T, Inky>) {
          ghost.setTarget(pacMan.positionInGrid(), pacMan.currentDirection(), std::get<Blinky>(ghosts).positionInGrid());
        }
      }(ghost),
       ...);
    },
    ghosts);

  fruit.update(delta, score.eatenPellets);

  std::apply([this](auto &... ghost) {
    (checkCollision(ghost), ...);
  },
             ghosts);

  eatPellets();
  eatFruit();
}

void GameState::checkCollision(Ghost & ghost) {
  if (isPacManDying() || ghost.isEyes())
    return;

  // TODO: hitboxes based collision
  if (ghost.positionInGrid() != pacMan.positionInGrid())
    return;

  if (ghost.isFrightened()) {
    ghost.die();
    score.points += GHOST_POINTS;
  } else {
    killPacMan();
  }
}

void GameState::handleDeathAnimation(std::chrono::milliseconds delta) {
  timeSinceDeath += delta;

  if (timeSinceDeath.count() > 1000) {
    std::apply([](auto &... ghost) {
      (ghost.reset(), ...);
    },
               ghosts);

    pacMan.reset();
    timeSinceDeath = std::chrono::milliseconds(0);
  }
}

void GameState::eatPellets() {
  const auto pos = pacMan.positionInGrid();
  if (pellets.eatPelletAtPosition(pos)) {
    score.eatenPellets++;
    score.points += NORMAL_PELLET_POINTS;
  }

  if (superPellets.eatPelletAtPosition(pos)) {
    score.eatenPellets++;
    score.points += POWER_PELLET_POINTS;

    std::apply([](auto &... ghost) {
      (ghost.frighten(), ...);
    },
               ghosts);
  }
}

void GameState::eatFruit() {
  const auto pos = pacMan.positionInGrid();
  const auto fruitpos = positionToGridPosition(fruit.position());

  // TODO: hitboxes based collision
  if (fruit.isVisible() && pos == fruitpos) {
    score.points += fruit.eat();
    score.eatenFruits++;
  }
}

void GameState::killPacMan() {
  pacMan.die();
  score.lives--;
  timeSinceDeath = std::chrono::milliseconds(1);
}

bool GameState::isPacManDying() const {
  return timeSinceDeath.count() != 0;
}

} // namespace pacman

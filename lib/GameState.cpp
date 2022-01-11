#include "GameState.hpp"

namespace ms_pacman {

constexpr int GHOST_POINTS = 200;
constexpr int NORMAL_PELLET_POINTS = 10;
constexpr int POWER_PELLET_POINTS = 50;

void GameState::step(std::chrono::milliseconds delta) {
  pacMan.update(delta, inputState.direction(), board);

  if (isPacManDying()) {
    handleDeathAnimation(delta);
    return;
  }

  if (!pacMan.hasDirection())
    return;

  std::apply(
    [ this, &delta ]<typename... Ghost>(Ghost & ... ghost) {
      ([&]<typename T>(T & ghost) {
        ghost.update(delta, board);
        if constexpr (std::is_same_v<T, Blinky>) {
          ghost.setTarget(board, pacMan.position());
        }
        if constexpr (std::is_same_v<T, Pinky>) {
          ghost.setTarget(board, pacMan.positionInGrid(), pacMan.currentDirection());
        }
        if constexpr (std::is_same_v<T, Inky>) {
          ghost.setTarget(board, pacMan.positionInGrid(), pacMan.currentDirection(), std::get<Blinky>(ghosts).positionInGrid());
        }
      }(ghost),
       ...);
    },
    ghosts);

  std::visit([&](auto && fruit){ fruit.update(delta, score.eatenPellets); }, currentFruit);

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
    }, cell);
    if(eaten)
        board[pos.y][pos.x] = Walkable{};
}

void GameState::eatFruit() {
  const auto pos = pacMan.positionInGrid();
  const auto fruitpos = positionToGridPosition(Fruits::position(currentFruit));

  // TODO: hitboxes based collision
  if (Fruits::isVisible(currentFruit) && pos == fruitpos) {
    score.points += Fruits::eat(currentFruit);
    score.eatenFruits.emplace_back(currentFruit);
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

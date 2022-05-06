#pragma once

#include <tuple>

#include "Fruit.hpp"
#include "Ghost.hpp"
#include "HighScore.hpp"
#include "InputState.hpp"
#include "Level.hpp"
#include "MsPacMan.hpp"
#include "Score.hpp"

namespace ms_pacman {

constexpr int GHOST_POINTS = 200;

using Ghosts = std::tuple<Blinky, Pinky, Inky, Clyde>;
using FruitCollection = std::vector<GenericFruit>;

struct GameState {
  ~GameState();
  void step(std::chrono::milliseconds delta);

  Ghosts ghosts;
  MsPacMan msPacMan;
  InputState inputState;
  FruitCollection fruits = { Cherry{}, Strawberry{}, Orange{}, Pretzel{}, Apple{}, Pear{}, Banana{} };
  size_t levelNum = 0;
  Level level = getLevel(levelNum);
  DefaultBoard board;
  bool game_over = false;
  Score score;
  HighScore highScore{ "highscore.txt" };
  std::chrono::milliseconds timeSinceDeath{};

  template<typename Ghost>
  void checkCollision(Ghost & ghost) {
    if (isMsPacManDying() || ghost.isEyes())
      return;

    // TODO: hitboxes based collision
    if (!isSamePosition(ghost.positionInGrid(), msPacMan.positionInGrid()))
      return;

    if (ghost.isFrightened()) {
      ghost.die();
      score.points += GHOST_POINTS;
    } else {
      killMsPacMan();
    }
  }

  bool stepMsPacMan(std::chrono::milliseconds & delta, MsPacMan & ms_pac_man);
  void stepGhosts(const std::chrono::milliseconds & delta, Ghosts & ghost_tuple);
  void checkCollision(Ghosts & ghost_tuple);
  void stepPellets(DefaultBoard & grid);
  void stepFruit(std::chrono::milliseconds delta, GenericFruit & fruit);
  void handleDeathAnimation(std::chrono::milliseconds delta);
  void killMsPacMan();
  bool isMsPacManDying() const;
  void increaseLevel();
  void loadLevel();
  bool isLevelCompleted() const;
  void reset();
  void restartGame();
  bool isGameOver() const;
  void setGameOver();
  size_t fruitIndex() const { return levelNum % fruits.size(); }
  GenericFruit & currentFruit() { return fruits[fruitIndex()]; }
};

} // namespace ms_pacman

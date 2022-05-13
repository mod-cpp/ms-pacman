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

using Ghosts = std::tuple<Blinky, Pinky, Inky, Sue>;
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
  Portals portals;
  GridPosition fruitPortal;
  bool game_over = false;
  Score score;
  HighScore highScore{ "highscore.txt" };
  DeltaTimer timerSinceDeath{ std::chrono::seconds(0) };

  template<typename Ghost>
  void checkCollision(Ghost & ghost) {
    if (isMsPacManDying() || ghost.isEyes())
      return;

    if (!isSamePosition(ghost.positionInGrid(), msPacMan.positionInGrid()))
      return;

    if (ghost.isFrightened()) {
      score.add(ghost);
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
  void loadBoard(std::tuple<DefaultBoard, Portals> board);
  void choseFruitPortal();
};

} // namespace ms_pacman

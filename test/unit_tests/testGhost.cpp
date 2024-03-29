#include "Ghost.hpp"
#include <catch2/catch_all.hpp>

template<typename T>
static void ghostInitTest(const T & ghost, double x, double y) {
  const ms_pacman::Position pos{ x, y };
  REQUIRE(isSamePosition(ghost.position(), pos));

  const ms_pacman::GridPosition gridPos = ms_pacman::positionToGridPosition(pos);
  REQUIRE(isSamePosition(ghost.positionInGrid(), gridPos));

  REQUIRE_FALSE(ghost.isEyes());
  REQUIRE_FALSE(ghost.isFrightened());
}

TEST_CASE("Ghosts start in the correct position", "[ghosts]") {
  ms_pacman::Blinky blinky;
  ghostInitTest(blinky, 13.5, 11);

  ms_pacman::Inky inky;
  ghostInitTest(inky, 13.5, 14);

  ms_pacman::Pinky pinky;
  ghostInitTest(pinky, 11.5, 14);

  ms_pacman::Sue sue;
  ghostInitTest(sue, 15.5, 14);
}

template<typename T>
static void ghostFrightenTest(T & ghost) {
  REQUIRE_FALSE(ghost.isFrightened());
  ghost.frighten();
  REQUIRE(ghost.isFrightened());
  ghost.reset();
  REQUIRE_FALSE(ghost.isFrightened());
}

TEST_CASE("Ghosts are frighten", "[ghosts]") {
  ms_pacman::Blinky blinky;
  ghostFrightenTest(blinky);

  ms_pacman::Inky inky;
  ghostFrightenTest(inky);

  ms_pacman::Pinky pinky;
  ghostFrightenTest(pinky);

  ms_pacman::Sue sue;
  ghostFrightenTest(sue);
}

template<typename T>
static void ghostDeadTest(T & ghost) {
  REQUIRE_FALSE(ghost.isEyes());
  ghost.die();
  REQUIRE(ghost.isEyes());
  ghost.reset();
  REQUIRE_FALSE(ghost.isEyes());
}

TEST_CASE("Ghosts can die", "[ghosts]") {
  ms_pacman::Blinky blinky;
  ghostDeadTest(blinky);

  ms_pacman::Inky inky;
  ghostDeadTest(inky);

  ms_pacman::Pinky pinky;
  ghostDeadTest(pinky);

  ms_pacman::Sue sue;
  ghostDeadTest(sue);
}

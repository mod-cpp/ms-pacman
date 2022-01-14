#include "Board.hpp"
#include <catch2/catch.hpp>

// These tests assume a static game board.

/*
TEST_CASE("Is walkable for Pac-Man", "[board]") {
  REQUIRE_FALSE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 0, 0 }));   // wall
  REQUIRE_FALSE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 27, 0 }));  // wall
  REQUIRE_FALSE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 0, 30 }));  // wall
  REQUIRE_FALSE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 27, 30 })); // wall
  REQUIRE_FALSE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 11, 13 })); // pen

  REQUIRE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 1, 1 }));   // pellet
  REQUIRE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 1, 3 }));   // power pellet
  REQUIRE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 1, 14 }));  // nothing
  REQUIRE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 0, 14 }));  // portal left
  REQUIRE(ms_pacman::isWalkableForPacMan(ms_pacman::GridPosition{ 27, 14 })); // portal right
  /
}

TEST_CASE("Is walkable for Ghost", "[board]") {
  const ms_pacman::GridPosition pen = ms_pacman::GridPosition{ 11, 13 };
  const ms_pacman::GridPosition outside = ms_pacman::GridPosition{ 1, 1 };

  // wall check
  REQUIRE_FALSE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 0, 0 }, outside, false));   // wall
  REQUIRE_FALSE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 27, 0 }, outside, false));  // wall
  REQUIRE_FALSE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 0, 30 }, outside, false));  // wall
  REQUIRE_FALSE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 27, 30 }, outside, false)); // wall

  // eyes can walk anywhere except walls
  REQUIRE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 11, 13 }, outside, true)); // pen
  REQUIRE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 1, 1 }, outside, true));   // pellet
  REQUIRE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 1, 3 }, outside, true));   // power pellet
  REQUIRE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 1, 14 }, outside, true));  // nothing
  REQUIRE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 0, 14 }, outside, true));  // portal left
  REQUIRE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 27, 14 }, outside, true)); // portal right

  // can only walk in pen if that is your origin or current location
  REQUIRE_FALSE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 11, 13 }, outside, false)); // in pen, origin outside
  REQUIRE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 1, 1 }, outside, false));         // outside, origin outside
  REQUIRE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 1, 1 }, pen, false));             // outside, origin pen
  REQUIRE(ms_pacman::isWalkableForGhost(ms_pacman::GridPosition{ 11, 13 }, pen, false));           // in pen, origin pen
}

TEST_CASE("Is portal", "[board]") {
  const ms_pacman::GridPosition portalRight = ms_pacman::GridPosition{ 27, 14 };
  const ms_pacman::GridPosition portalLeft = ms_pacman::GridPosition{ 0, 14 };

  REQUIRE(ms_pacman::isPortal(portalRight, ms_pacman::Direction::RIGHT));      // right into right portal
  REQUIRE(ms_pacman::isPortal(portalLeft, ms_pacman::Direction::LEFT));        // left into left portal
  REQUIRE_FALSE(ms_pacman::isPortal(portalRight, ms_pacman::Direction::LEFT)); // left into right portal
  REQUIRE_FALSE(ms_pacman::isPortal(portalLeft, ms_pacman::Direction::RIGHT)); // right into left portal
}

TEST_CASE("Teleport", "[board]") {
  const ms_pacman::GridPosition portalRight = ms_pacman::GridPosition{ 27, 14 };
  const ms_pacman::GridPosition portalLeft = ms_pacman::GridPosition{ 0, 14 };

  if (ms_pacman::isPortal(portalRight, ms_pacman::Direction::RIGHT)) {
    const ms_pacman::GridPosition result = ms_pacman::teleport(portalRight);
    REQUIRE(result.x == portalLeft.x);
  }

  if (ms_pacman::isPortal(portalLeft, ms_pacman::Direction::LEFT)) {
    const ms_pacman::GridPosition result = ms_pacman::teleport(portalLeft);
    REQUIRE(result.x == portalRight.x);
  }
}
*/

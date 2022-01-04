#include "Position.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Position are properly initialized", "[positions]") {
  ms_pacman::Position pos;
  REQUIRE(pos.x == Approx(0.0));
  REQUIRE(pos.y == Approx(0.0));

  ms_pacman::Position pos2{ 10.0, 20.0 };
  REQUIRE(pos2.x == Approx(10.0));
  REQUIRE(pos2.y == Approx(20.0));
}

TEST_CASE("GridPosition are properly initialized", "[positions]") {
  ms_pacman::GridPosition gridPos{ 10, 20 };
  REQUIRE(gridPos.x == 10);
  REQUIRE(gridPos.y == 20);
}

TEST_CASE("Position converts to GridPosition", "[positions]") {
  ms_pacman::Position pos{ 10.0, 20.0 };
  const auto gridPos = ms_pacman::positionToGridPosition(pos);
  REQUIRE(gridPos.x == 10);
  REQUIRE(gridPos.y == 20);
}

TEST_CASE("GridPosition converts to Position", "[positions]") {
  ms_pacman::GridPosition gridPos{ 10, 20 };
  const auto pos = ms_pacman::gridPositionToPosition(gridPos);
  REQUIRE(pos.x == Approx(10.0));
  REQUIRE(pos.y == Approx(20.0));
}

TEST_CASE("Positions compare equal", "[positions]") {
  ms_pacman::Position pos1{ 10.0, 20.0 };
  ms_pacman::Position pos2{ 10.0, 20.0 };
  REQUIRE(pos1 == pos2);

  ms_pacman::Position pos3{ 9.9, 19.9 };
  REQUIRE_FALSE(pos1 == pos3);

  pos3.x += 0.1;
  pos3.y += 0.1;

  REQUIRE(pos1 == pos3);
}

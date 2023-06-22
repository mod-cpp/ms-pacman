#include <catch2/catch_all.hpp>

#include "Cheats.hpp"

using namespace ms_pacman;

TEST_CASE("Happy Day: SuperSpeed", "[cheats]") {
  Cheats cheats;
  auto first = cheats.add_cheat(Code::F);
  CHECK(!first);
  auto second = cheats.add_cheat(Code::O);
  CHECK(!second);
  auto third = cheats.add_cheat(Code::X);
  REQUIRE(third.has_value());
  CHECK(third.value() == Cheat::SuperSpeed);
}

TEST_CASE("Invalid : Foo", "[cheats]") {
  Cheats cheats;
  auto first = cheats.add_cheat(Code::F);
  CHECK(!first);
  auto second = cheats.add_cheat(Code::O);
  CHECK(!second);
  auto third = cheats.add_cheat(Code::O);
  REQUIRE(!third);
}

TEST_CASE("Getting to: SuperSpeed", "[cheats]") {
  Cheats cheats;
  for (int i = 0; i < 10; i++) {
    auto fake = cheats.add_cheat(Code::F);
    CHECK(!fake);
  }

  auto first = cheats.add_cheat(Code::F);
  CHECK(!first);
  auto second = cheats.add_cheat(Code::O);
  CHECK(!second);
  auto third = cheats.add_cheat(Code::X);
  REQUIRE(third.has_value());
  CHECK(third.value() == Cheat::SuperSpeed);
}

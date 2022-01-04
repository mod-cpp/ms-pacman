#pragma once

#include "Board.hpp"
#include "Position.hpp"

namespace ms_pacman {

class SuperPellets {
public:
  SuperPellets();

  GridPosition currentSprite() const {
    return sprite;
  }

  std::vector<GridPosition> allPellets() const {
    return positions;
  }

  bool eatPelletAtPosition(GridPosition p);

private:
  const GridPosition sprite = { 0, 9 };
  std::vector<GridPosition> positions;
};

} // namespace pacman

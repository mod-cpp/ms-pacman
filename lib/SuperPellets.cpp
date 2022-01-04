#include "SuperPellets.hpp"
#include <algorithm>

namespace ms_pacman {

SuperPellets::SuperPellets()
  : positions(initialSuperPelletPositions()) {}

bool SuperPellets::eatPelletAtPosition(GridPosition p) {
  auto it = std::find(positions.begin(), positions.end(), p);
  if (it == positions.end())
    return false;
  positions.erase(it);
  return true;
}

} // namespace pacman

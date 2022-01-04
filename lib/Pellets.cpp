#include "Pellets.hpp"
#include <algorithm>

namespace ms_pacman {

Pellets::Pellets()
  : positions(initialPelletPositions()) {}

bool Pellets::eatPelletAtPosition(GridPosition p) {
    for(auto it = positions.begin(); it != positions.end(); ++it) {
        if(*it == p) {
            positions.erase(it);
            return true;
        }
    }
    return false;
}

} // namespace pacman

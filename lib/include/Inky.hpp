#pragma once

#include "Ghost.hpp"

namespace ms_pacman {

class Inky final : public Ghost {
public:
  Inky();
  void setTarget(const DefaultBoard & board, GridPosition pacManPos, Direction pacManDir, GridPosition blinkyPos);

protected:
  double speed() const override;
  Position initialPosition() const override;

private:
  Position scatterTarget() const;
};

} // namespace ms_pacman

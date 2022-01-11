#pragma once

#include "Ghost.hpp"

namespace ms_pacman {

class Pinky final : public Ghost {
public:
  Pinky();
  void setTarget(const DefaultBoard & board, GridPosition pacManPos, Direction pacManDir);

protected:
  double speed() const override;
  Position initialPosition() const override;

private:
  Position scatterTarget() const;
};

} // namespace ms_pacman

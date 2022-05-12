#pragma once

#include "AtlasGhosts.hpp"
#include "Board.hpp"
#include "GhostState.hpp"
#include "NPC.hpp"

#include <numeric>

namespace ms_pacman {

template<typename Ghost>
class GhostBase : public NPC {
public:
  GhostBase(const Atlas::Ghost spriteSet, const Position position, const Position scatterTarget)
    : NPC(position, scatterTarget),
      spriteSet(spriteSet) {}

  double speed() const override {
    if (state == GhostState::Eyes)
      return 2;
    if (state == GhostState::Frightened)
      return 0.5;
    return 0.75;
  }

  bool isWalkable(const DefaultBoard & board, GridPosition current_position, GridPosition target_position) const override {
    return isWalkableForGhost(board, current_position, target_position, isEyes());
  }

  constexpr bool isInPen(const DefaultBoard & board) const {
    return ms_pacman::isInPen(board, positionInGrid());
  }

  bool isFrightened() const {
    return state == GhostState::Frightened;
  }

  bool isEyes() const {
    return state == GhostState::Eyes;
  }

  GridPosition currentSprite() const {
    switch (state) {
      default:
        return Atlas::ghostSprite(spriteSet, direction, (animationIndex % 2) == 0);
      case GhostState::Eyes:
        return Atlas::eyeSprite(direction);
      case GhostState::Frightened:
        if (timeFrighten.count() < 3500)
          return Atlas::initialFrightened(animationIndex);
        else
          return Atlas::endingFrightened(animationIndex);
    }
  }

  void update(std::chrono::milliseconds time_delta, const DefaultBoard & board) {
    if (state == GhostState::Eyes && isInPen(board)) {
      state = GhostState::Scatter;
    }

    if (state == GhostState::Frightened) {
      timeFrighten += time_delta;
      if (timeFrighten.count() > 6000)
        state = GhostState::Scatter;
    }

    if (state == GhostState::Scatter || state == GhostState::Chase) {
      timeChase += time_delta;
      const auto newState = defaultStateAtDuration(std::chrono::duration_cast<std::chrono::seconds>(timeChase));
      if (newState != state) {
        direction = oppositeDirection(direction);
        state = newState;
      }
    }

    updateAnimation(time_delta);
    updatePosition(time_delta, board);
  }

  GhostState defaultStateAtDuration(std::chrono::seconds seconds) const {
    // This array denotes the duration of each state, alternating between scatter and chase
    std::array changes = { /*scatter*/ 7, 20, 7, 20, 5, 20, 5 };

    // To know the current state we first compute the cumulative time using std::partial_sum
    // This gives us {7, 27, 34, 54, 59, 79, 84}
    std::partial_sum(std::begin(changes), std::end(changes), std::begin(changes));

    // Then we look for the first value in the array greater than the time spent in chase/scatter states
    auto it = std::upper_bound(std::begin(changes), std::end(changes), seconds.count());

    // We get the position of that iterator in the array
    auto count = std::distance(std::begin(changes), it);

    // Because the first position is scatter, all the even positions will be "scatter"
    // all the odd positions will be "chase"
    return count % 2 == 0 ? GhostState::Scatter : GhostState::Chase;
  }

  void updateAnimation(std::chrono::milliseconds time_delta) {
    timeForAnimation += double(time_delta.count());
    if (timeForAnimation >= 250) {
      timeForAnimation = 0;
      animationIndex = (animationIndex + 1) % 4;
    }
  }

  void die() {
    if (state == GhostState::Eyes)
      return;

    direction = oppositeDirection(direction);
    state = GhostState::Eyes;
    timeFrighten = {};
    timeChase = {};
  }

  void reset() {
    pos = Ghost::initialPosition;
    state = GhostState::Scatter;
    timeFrighten = {};
    timeChase = {};
  }

  void frighten() {
    if (state > GhostState::Scatter)
      return;

    direction = oppositeDirection(direction);
    state = GhostState::Frightened;
    timeFrighten = {};
  }

protected:
  GhostState state = GhostState::Chase;
  Atlas::Ghost spriteSet;
  double timeForAnimation = 0;
  std::size_t animationIndex = 0;
  std::chrono::milliseconds timeFrighten = {};
  std::chrono::milliseconds timeChase = {};
};

} // namespace ms_pacman

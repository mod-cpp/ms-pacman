#pragma once

#include <chrono>

namespace ms_pacman {

class DeltaTimer {
public:
  explicit DeltaTimer(std::chrono::milliseconds limit)
    : limit(limit) {}
  void inc(std::chrono::milliseconds delta) { timer += delta; }
  bool timed_out() const { return timer > limit; }
  void reset() { timer = std::chrono::seconds{ 0 }; }

private:
  std::chrono::milliseconds timer{ 0 };
  const std::chrono::milliseconds limit;
};

} // namespace ms_pacman

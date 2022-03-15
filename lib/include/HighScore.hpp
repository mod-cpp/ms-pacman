#pragma once

#include "HighScoreFile.hpp"

struct player {
  player(std::string name, int score) : name(std::move(name)), score(score) {}
  std::string name;
  int score = 0;
};

class HighScore {
public:
  int top() const;
  void populate(HighScoreFile file);

  size_t num_players() const;

private:
  std::vector<player> high_scores;
};

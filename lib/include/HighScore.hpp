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
  void populate(std::vector<std::tuple<std::string, int>> list);

  size_t num_players() const;

private:
  std::vector<player> high_scores;
};

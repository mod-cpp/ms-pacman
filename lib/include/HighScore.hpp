#pragma once

#include "HighScoreFile.hpp"

struct player {
  player(std::string name, int score) : name(std::move(name)), score(score) {}
  std::string name;
  int score = 0;
};

using ParsedInput = std::vector<std::tuple<std::string, int>>;

class HighScore {
public:
  int top() const;
  ParsedInput parse(std::string input);
  void populate(std::vector<std::tuple<std::string, int>> list);

  size_t num_players() const;

private:
  std::vector<player> high_scores;
};

#pragma once

#include "HighScoreFile.hpp"

namespace ms_pacman {

struct player {
  player(std::string name, int score)
    : name(std::move(name)),
      score(score) {}
  std::string name;
  int score = 0;
};

using ParsedInput = std::vector<std::tuple<std::string, int>>;

class HighScore final {
public:
  explicit HighScore(std::string save_filename);
  ~HighScore();
  int top() const;
  ParsedInput parse(std::string input);
  void populate(std::vector<std::tuple<std::string, int>> list);
  void insert(std::string, int);

  size_t num_players() const;

  void initialize(HighScoreFile file);

  void save() const;

  void saveScore(int);

private:
  std::vector<player> high_scores;
  std::string filename;
};

}

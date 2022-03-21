#pragma once

#include "HighScoreFile.hpp"

#include <unordered_map>

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
  ParsedInput parse(std::string input) const;
  void populate(std::vector<std::tuple<std::string, int>> list);
  void insert(const std::string&, int);

  size_t num_players() const;

  void initialize(HighScoreFile file);

  void save() const;

  void saveScore(int);

private:
  std::unordered_map<std::string, player> high_scores;
  std::string filename;
};

}

#pragma once

#include "HighScoreFile.hpp"

#include <span>
#include <unordered_map>

namespace ms_pacman {

struct player {
  player(std::string name, int score)
    : name(std::move(name)),
      score(score) {}
  std::string name;
  int score = 0;
};

using PlayerScore = std::tuple<std::string, int>;
using Scores = std::vector<PlayerScore>;

class HighScore final {
public:
  explicit HighScore(std::string save_filename);
  ~HighScore();
  int top() const;
  Scores parse(const std::string & file_content) const;
  void populate(const std::span<PlayerScore> & list);
  void insert(const std::string &, int);
  size_t num_players() const;

  void initialize(HighScoreFile file);

  void save() const;

  void saveScore(int);

private:
  std::unordered_map<std::string, player> high_scores;
  std::string filename;
};

} // namespace ms_pacman

#include "HighScore.hpp"
#include "HighScoreFile.hpp"

#include <algorithm>

int HighScore::top() const {
  if (high_scores.empty())
    return 0;
  return high_scores.front().score;
}

void HighScore::populate(HighScoreFile file) {
  const auto & list = file.parsed_data();
  for (auto && [name, score] : list)
    high_scores.emplace_back(name, score);
  auto comp = [](const player & first, const player & second){
    return first.score > second.score;
  };
  std::sort(high_scores.begin(), high_scores.end(), comp);
}

size_t HighScore::num_players() const {
  return high_scores.size();
}

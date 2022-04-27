#include "HighScore.hpp"
#include "HighScoreFile.hpp"
#include "User.hpp"

#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <fmt/printf.h>
#include <memory>
#include <sstream>
#include <utility>

namespace ms_pacman {

static std::tuple<std::string, int> split_line(const std::string & line) {
  auto index = line.find(',');
  std::string player_name = line.substr(0, index);
  std::string score_str = line.substr(index + 1);
  int score{};
  std::from_chars(score_str.data(), score_str.data() + score_str.size(), score);
  return { player_name, score };
}

HighScore::HighScore(std::string save_filename) : filename(std::move(save_filename)) {
  initialize(HighScoreFile(filename));
}

int HighScore::top() const {
  if (high_scores.empty())
    return 0;
  auto it = std::max_element(high_scores.begin(),
                             high_scores.end(),
                             [](const auto & player_one, const auto & player_two) {
                               return player_one.second.score < player_two.second.score;
                             });
  auto [name, player] = *it;
  return player.score;
}

void HighScore::populate(const std::vector<PlayerScore>& list) {
  for (auto && [name, score] : list)
    high_scores.emplace(name, player{ name, score });
}

void HighScore::insert(const std::string& name, int score) {
  high_scores.insert_or_assign(name, player{ name, score });
}

Scores HighScore::parse(const std::string& file_content) const {
  std::vector<PlayerScore> scores;
  auto stream = std::stringstream(file_content);
  std::string line;
  while (std::getline(stream, line)) {
    auto [name, score] = split_line(line);
    scores.emplace_back(name, score);
  }
  return scores;
}

size_t HighScore::num_players() const {
  return high_scores.size();
}

void HighScore::initialize(HighScoreFile file) {
  if (!file.is_valid())
    return;
  auto data = parse(file.read_all());
  populate(data);
}

void HighScore::save() const {
  std::unique_ptr<FILE, decltype(&fclose)> file(fopen(filename.c_str(), "w"), &fclose);
  if (!file)
    return;
  for (const auto & [name, player] : high_scores) {
    fmt::print(file.get(), "{},{}\n", name, player.score);
  }
}

void HighScore::saveScore(int score) {
  if (score == 0)
    return;
  insert(userlogin(), score);
  save();
}

HighScore::~HighScore() {
  save();
}

}

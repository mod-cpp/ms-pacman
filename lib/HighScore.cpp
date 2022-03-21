#include "HighScore.hpp"
#include "HighScoreFile.hpp"
#include "User.hpp"

#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <fmt/printf.h>
#include <memory>
#include <sstream>

static std::tuple<std::string, int> split_line(std::string_view line) {
  auto index = line.find(',');
  std::string_view name = line.substr(index + 1);
  int score{};
  std::from_chars(name.data(), name.data() + name.size(), score);
  return { std::string(line.substr(0, index)), score };
}

namespace ms_pacman {

HighScore::HighScore(std::string save_filename) : filename(save_filename) {
  initialize(HighScoreFile(filename));
}

int HighScore::top() const {
  if (high_scores.empty())
    return 0;
  auto it = std::max_element(high_scores.begin(),
                             high_scores.end(),
                             [](const auto & player_one, const auto & player_two) {
                               return player_one.second.score > player_two.second.score;
                             });
  auto [name, player] = *it;
  return player.score;
}

void HighScore::populate(std::vector<std::tuple<std::string, int>> list) {
  for (auto && [name, score] : list)
    high_scores.emplace(name, player{ name, score });
}

void HighScore::insert(const std::string& name, int score) {
  high_scores.insert_or_assign(name, player{ name, score });
}

ParsedInput HighScore::parse(std::string input) const {
  std::vector<std::tuple<std::string, int>> parsed_input;
  size_t num_lines = 0;
  auto stream = std::stringstream(input);
  for (std::string line; std::getline(stream, line); num_lines++) {
    parsed_input.push_back(split_line(line));
  }
  return parsed_input;
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

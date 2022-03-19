#include "HighScore.hpp"
#include "HighScoreFile.hpp"
#include "fmt/printf.h"
#include <algorithm>
#include <charconv>
#include <cstdlib>
#include <memory>
#include <sstream>

static std::tuple<std::string, int> split_line(std::string_view line) {
  auto index = line.find(',');
  std::string_view name = line.substr(index + 1);
  int score{};
  std::from_chars(name.data(), name.data() + name.size(), score);
  return { std::string(line.substr(0, index)), score };
}

int HighScore::top() const {
  if (high_scores.empty())
    return 0;
  return high_scores.front().score;
}

void HighScore::populate(std::vector<std::tuple<std::string, int>> list) {
  for (auto && [name, score] : list)
    high_scores.emplace_back(name, score);
  auto comp = [](const player & first, const player & second) {
    return first.score > second.score;
  };
  std::sort(high_scores.begin(), high_scores.end(), comp);
}

void HighScore::insert(std::string name, int score) {
  auto comp = [](const player & first, const player & second) {
    return first.score > second.score;
  };
  player p{ std::move(name), score };
  high_scores.insert(std::lower_bound(high_scores.begin(),
                                      high_scores.end(),
                                      p,
                                      comp),
                     p);
}

ParsedInput HighScore::parse(std::string input) {
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

void HighScore::save(std::string save) {
  std::unique_ptr<FILE, decltype(&fclose)> file(fopen(save.c_str(), "w"), &fclose);
  if (!file)
    return;
  for (const auto & [name, score] : high_scores) {
    fmt::print(file.get(), "{},{}\n", name, score);
  }
}

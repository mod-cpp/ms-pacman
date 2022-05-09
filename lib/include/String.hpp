#pragma once

#include <charconv>
#include <string>
#include <tuple>

namespace ms_pacman::String {

static std::tuple<std::string, int> split(const std::string & line) {
  auto index = line.find(',');
  std::string player_name = line.substr(0, index);
  std::string score_str = line.substr(index + 1);
  int score{};
  std::from_chars(score_str.data(), score_str.data() + score_str.size(), score);
  return { player_name, score };
}

} // namespace ms_pacman::String

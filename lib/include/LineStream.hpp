#pragma once

#include <optional>
#include <sstream>
#include <string>
#include <charconv>

namespace ms_pacman {

class LineStream {
public:
  explicit LineStream(const std::string & str)
    : stream(str) {}

  std::optional<std::string> next() {
    std::string line;
    if (std::getline(stream, line))
      return { line };
    return {};
  }

  static std::tuple<std::string, int> split(const std::string & line) {
    auto index = line.find(',');
    std::string player_name = line.substr(0, index);
    std::string score_str = line.substr(index + 1);
    int score{};
    std::from_chars(score_str.data(), score_str.data() + score_str.size(), score);
    return { player_name, score };
  }

private:
  std::stringstream stream;
};

} // namespace ms_pacman
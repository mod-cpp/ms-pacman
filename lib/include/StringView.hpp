#pragma once

#include <algorithm>
#include <charconv>
#include <string>
#include <string_view>

namespace ms_pacman::StringView {

inline std::string to_upper(std::string_view word) {
  // Exercise 421: Make whole word uppercase
  return std::string{ word };
}

inline std::string trim(std::string_view view) {
  // Exercise 422 : Trim leading and trailing white space
  return std::string{ view };
}

inline std::vector<std::string> split(std::string_view view) {
  // Exercise 423 : Split view into tokens based on whitespace
  return { std::string{ view } };
}

inline std::vector<std::string> split(std::string_view view, char delimiter) {
  // Exercise 424 : Split view into tokens based on delimiter
  std::vector<std::string> tokens;
  auto index = view.find(delimiter);
  tokens.emplace_back(view.substr(0, index));
  tokens.emplace_back(view.substr(index + 1));
  return tokens;
}

inline int to_int(std::string_view /*word*/) {
  int value{};
  // Exercise 425 : Get int from string
  return value;
}

} // namespace ms_pacman::StringView

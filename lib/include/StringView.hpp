#pragma once

#include <algorithm>
#include <string>
#include <string_view>

namespace ms_pacman::StringView {

std::string to_upper(std::string_view /*word*/) {
  std::string ret;
  // Make whole word uppercase
  return ret;
}

std::string trim(std::string_view /*view*/) {
  // Exercise 422 : Trim leading and trailing white space
  return {};
}

std::vector<std::string> split(std::string_view /*view*/) {
  std::vector<std::string> tokens;
  // Split view into tokens based on whitespace
  return tokens;
}

} // namespace ms_pacman::StringView

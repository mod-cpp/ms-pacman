#pragma once

#include <charconv>
#include <optional>
#include <sstream>
#include <string>

namespace ms_pacman {

class LineViewStream {
public:
  explicit LineViewStream(const std::string & str)
    : view(str) {}

  std::optional<std::string_view> next() {
    // Exercise 420
    return {};
  }

private:
  std::string_view view;
};

} // namespace ms_pacman

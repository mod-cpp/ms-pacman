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

private:
  std::stringstream stream;
};

} // namespace ms_pacman
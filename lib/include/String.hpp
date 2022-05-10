#pragma once

#include <string>
#include <tuple>
#include <cassert>
#include "StringView.hpp"

namespace ms_pacman::String {

static std::tuple<std::string, int> get_player_score(const std::string & line) {
  std::vector<std::string> parts = StringView::split(line, ',');
  auto player_name = StringView::to_upper(StringView::trim(parts[0]));
  auto player_score = StringView::to_int(parts[1]);
  return { player_name, player_score };
}

} // namespace ms_pacman::String

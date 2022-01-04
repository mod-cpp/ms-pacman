#pragma once
#include <array>
#include <string_view>

struct Level {
    std::string_view background;
    std::string_view data;
};

constexpr std::array levels = {
  Level{ "maze1.png", "maze1_data.png" },
  Level{ "maze2.png", "maze2_data.png" },
  Level{ "maze3.png", "maze3_data.png" },
  Level{ "maze4.png", "maze4_data.png" }
};

constexpr Level getLevel(int n){
    return levels[n];
}

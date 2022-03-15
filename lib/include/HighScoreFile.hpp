#pragma once

#include <string>
#include <tuple>
#include <vector>

class HighScoreFile {
public:
  explicit HighScoreFile(std::string filename);
  virtual ~HighScoreFile();

  HighScoreFile(HighScoreFile&& other);

  bool is_valid() const;
  bool load();
  size_t parse();

  const auto & parsed_data() const {
    return parsed_input;
  }

private:
  std::string name;
  std::FILE* file = nullptr;
  std::string input;
  std::vector<std::tuple<std::string, int>> parsed_input;
};

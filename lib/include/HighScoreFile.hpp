#pragma once

#include <string>
#include <vector>

class HighScoreFile {
public:
  explicit HighScoreFile(std::string filename);
  bool is_valid();

  bool load();
  virtual ~HighScoreFile();

  size_t parse();

private:
  std::string name;
  std::FILE* file = nullptr;
  std::string input;
  std::vector<std::tuple<std::string, int>> parsed_input;
};

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
  std::string load();
  std::vector<std::tuple<std::string, int>> parse(std::string input);

private:
  std::FILE* file = nullptr;
};

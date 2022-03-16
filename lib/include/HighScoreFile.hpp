#pragma once

#include <string>
#include <tuple>
#include <vector>

class HighScoreFile {
public:
  explicit HighScoreFile(std::string filename);
  virtual ~HighScoreFile();

  HighScoreFile(HighScoreFile&& other);

  std::string load();

private:
  std::FILE* file = nullptr;
};

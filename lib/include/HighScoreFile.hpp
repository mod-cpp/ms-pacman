#pragma once

#include <string>
#include <tuple>
#include <vector>

class HighScoreFile {
public:
  explicit HighScoreFile(std::string filename);
  virtual ~HighScoreFile();

  HighScoreFile(const HighScoreFile &) = delete;
  HighScoreFile operator=(const HighScoreFile &) = delete;

  HighScoreFile(HighScoreFile&& other) noexcept;
  HighScoreFile operator=(HighScoreFile &&) = delete;

  std::string load();

private:
  std::string filename;
  std::FILE* file = nullptr;
  size_t get_size() const;
};

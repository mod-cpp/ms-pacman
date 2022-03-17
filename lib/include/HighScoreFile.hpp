#pragma once

#include <string>
#include <tuple>
#include <vector>

class HighScoreFile final {
public:
  explicit HighScoreFile(std::string filename);
  ~HighScoreFile();

  HighScoreFile(const HighScoreFile &) = delete;
  HighScoreFile& operator=(const HighScoreFile &) = delete;

  HighScoreFile(HighScoreFile&& other) noexcept;
  HighScoreFile& operator=(HighScoreFile &&) = delete;

  std::string read_all();

  bool is_valid() const;

private:
  std::string filename;
  std::FILE* file = nullptr;
  size_t get_size() const;
};

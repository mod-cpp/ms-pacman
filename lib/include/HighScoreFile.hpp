#pragma once

#include <cstdio>
#include <memory>
#include <string>

inline void closer(std::FILE * file) {
  if (file)
    std::fclose(file);
}

class HighScoreFile final {
public:
  explicit HighScoreFile(std::string name)
    : filename(std::move(name)),
      file(std::fopen(filename.c_str(), "r"), &closer){};

  std::string read_all();
  bool is_valid() const;

private:
  size_t get_size() const;

  std::string filename;
  std::unique_ptr<std::FILE, decltype(&closer)> file;
};

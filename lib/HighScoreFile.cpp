#include "HighScoreFile.hpp"

#include <cstdio>
#include <tuple>

HighScoreFile::HighScoreFile(std::string filename) :
    file(fopen( filename.c_str(), "r" )) {
}

HighScoreFile::~HighScoreFile() {
  if (file)
    std::fclose(file);
}

HighScoreFile::HighScoreFile(HighScoreFile && other) {
  std::swap(file, other.file);
}

std::string HighScoreFile::load() {
  std::string input;

  int c = 0;
  while ((c = std::fgetc(file)) != EOF) {
    input.push_back(static_cast<char>(c));
  }

  if (!std::ferror(file) && std::feof(file)) {
    return input;
  }

  return {};
}

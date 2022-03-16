#include "HighScoreFile.hpp"

#include <cstdio>
#include <filesystem>
#include <system_error>
#include <tuple>

HighScoreFile::HighScoreFile(std::string name) :
    filename(std::move(name)),
    file(fopen( filename.c_str(), "r" )) {
}

HighScoreFile::~HighScoreFile() {
  if (file)
    std::fclose(file);
}

HighScoreFile::HighScoreFile(HighScoreFile && other) noexcept {
  using std::swap;
  swap(file, other.file);
}

std::string HighScoreFile::load() {
  std::string input;
  input.reserve(get_size());

  int c = 0;
  while ((c = std::fgetc(file)) != EOF) {
    input.push_back(static_cast<char>(c));
  }

  if (!std::ferror(file) && std::feof(file)) {
    return input;
  }

  return {};
}

size_t HighScoreFile::get_size() {
  std::error_code ec;
  auto file_size = std::filesystem::file_size(filename, ec);
  return ec ? 0 : file_size;
}

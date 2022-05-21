#include "HighScoreFile.hpp"

#include <filesystem>
#include <system_error>

std::string HighScoreFile::read_all() {
  std::string input;
  input.reserve(get_size());

  auto done = [&](auto c) {
    return std::ferror(file.get()) || (c == EOF);
  };

  auto next = [&]() {
    return std::fgetc(file.get());
  };

  for (int c = next(); !done(c); c = next()) {
    input.push_back(static_cast<char>(c));
  }

  if (!std::ferror(file.get()) && std::feof(file.get())) {
    return input;
  }

  return {};
}

size_t HighScoreFile::get_size() const {
  std::error_code ec;
  auto file_size = std::filesystem::file_size(filename, ec);
  return ec ? 0 : file_size;
}

bool HighScoreFile::is_valid() const {
  return file != nullptr;
}

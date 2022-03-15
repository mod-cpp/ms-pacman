#include "HighScoreFile.hpp"

#include <charconv>
#include <cstdio>
#include <sstream>
#include <utility>
#include <tuple>

static std::tuple<std::string, int> split_line(std::string_view line) {
  auto index = line.find(',');
  std::string_view name = line.substr(index+1);
  int score{};
  std::from_chars(name.data(), name.data() + name.size(), score);
  return { std::string(line.substr(0, index)), score };
}


HighScoreFile::HighScoreFile(std::string filename) :
    name(std::move(filename)),
    file(fopen( name.c_str(), "r" )) {
  auto e = errno;
  (void) e;
}

HighScoreFile::~HighScoreFile() {
  if (file)
    std::fclose(file);
}

bool HighScoreFile::load() {
  input.clear();

  int c = 0;
  while ((c = std::fgetc(file)) != EOF) {
    input.push_back(static_cast<char>(c));
  }

  if (!std::ferror(file) && std::feof(file)) {
    return true;
  }

  return false;
}

bool HighScoreFile::is_valid() {
  return file != nullptr;
}

size_t HighScoreFile::parse() {
  size_t num_lines = 0;
  auto stream = std::stringstream(input);
  for(std::string line; std::getline(stream, line); num_lines++) {
    parsed_input.push_back(split_line(line));
  }
  return num_lines;
}

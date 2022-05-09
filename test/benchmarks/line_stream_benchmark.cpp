#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include "LineStream.hpp"
#include "LineViewStream.hpp"

#include <fstream>

std::string slurp(const std::string & filename) {
  auto file_stream = std::ifstream(filename);
  std::ostringstream output_stream;
  output_stream << file_stream.rdbuf();
  return output_stream.str();
}

size_t line_stream_lines(const std::string & contents) {
  ms_pacman::LineStream stream(contents);
  size_t num_lines = 0;
  while (auto line = stream.next()) {
    num_lines++;
  }
  return num_lines;
}

size_t line_view_stream_lines(const std::string & contents) {
  ms_pacman::LineViewStream stream(contents);
  size_t num_lines = 0;
  while (auto line = stream.next()) {
    num_lines++;
  }
  return num_lines;
}

TEST_CASE("Count lines in book", "[benchmark]") {

  std::string contents = slurp("book.txt");

  CHECK(contents.size() == 86586);

  BENCHMARK("LineViewStream") {
    size_t lines = line_view_stream_lines(contents);
    // REQUIRE(lines == 1950);
    return lines;
  };

  BENCHMARK("LineStream") {
    size_t lines = line_stream_lines(contents);
    REQUIRE(lines == 1950);
    return lines;
  };
}

[< Back](README.md)

# 41. std::string_view and std::span

* [Exercise 410](#exercise-410)
* [Exercise 412](#exercise-412)
* [Exercise 413](#exercise-413)
* [Exercise 414](#exercise-414)
* [Exercise 415](#exercise-415)

## Exercise 410

### Implement next() in LineViewStream.hpp

Run the benchmark:

<details>
   <summary>CMakePreset: <b>osx</b></summary>

```bash
cd cd build/osx/test/
./ms_pacman_benchmarks
```

</details>

<details>
   <summary>CMakePreset: <b>x64-windows</b></summary>

```bash
cd .\build\x64-windows\test\Debug\
.\ms_pacman_benchmarks.exe
```

</details>
<details>
   <summary>CMakePreset: <b>linux-gcc</b></summary>

```bash
cd build/linux-gcc/test
./ms_pacman_benchmarks
```

</details>
<details>
   <summary>CMakePreset: <b>linux-clang</b></summary>

```bash
cd build/linux-clang/test
./ms_pacman_benchmarks
```

</details>

Uncomment this line in the benchmark [line_stream_benchmark.cpp][5]

```cpp
    // REQUIRE(lines == 1950);
```

Implement the next function in [LineViewStream.hpp][6] trying not to make copies 
of the string except in the return statement.

Compare the performance with [LineStream.hpp][7] by running the benchmark in
[line_stream_benchmark.cpp][5].

```cpp
std::optional<std::string_view> next() {
    
}
```

<details>
   <summary>Solution</summary>

```cpp
  std::optional<std::string_view> next() {
    std::size_t pos = view.find('\n');
    if (pos == std::string::npos)
      return {};

    auto line = view.substr(0, pos);
    view.remove_prefix(pos + 1);
    return { line };
  }
```

</details>

## [Exercise 412][1]

### Trim leading and trailing white space from std::string_view in [StringView.hpp][8]

* [std::string_view][2]

```cpp
inline std::string trim(std::string_view view) {
  // Exercise 412 : Trim leading and trailing white space
  return std::string{ view };
}
```

<details>
   <summary>Solution</summary>

```cpp
inline std::string trim(std::string_view view) {
  auto start_it = std::find_if_not(view.begin(), view.end(), ::isspace);
  auto end_it = std::find_if_not(view.rbegin(), view.rend(), ::isspace);
  return std::string{ start_it, end_it.base() };
}
```

</details>

## [Exercise 413][1]

### Split std::string_view into tokens based on whitespace in [StringView.hpp][8]

```cpp
inline std::vector<std::string> split(std::string_view view) {
  // Exercise 413 : Split view into tokens based on whitespace
  return { std::string{ view } };
}
```

<details>
   <summary>Solution</summary>

```cpp
inline std::vector<std::string> split(std::string_view view) {
  std::vector<std::string> tokens;

  auto start = view.begin();
  const auto stop = view.end();

  while (start < stop) {
    auto start_word = std::find_if_not(start, stop, ::isspace);
    auto end_word = std::find_if(start_word, stop, ::isspace);
    tokens.emplace_back(start_word, end_word);
    start = end_word;
  }

  return tokens;
}
```

</details>

## [Exercise 414][1]

### Split view into tokens based on delimiter in [StringView.hpp][8]

```cpp
inline std::vector<std::string> split(std::string_view view, char delimiter) {
  // Exercise 414 : Split view into tokens based on delimiter
  std::vector<std::string> tokens;
  auto index = view.find(delimiter);
  tokens.emplace_back(view.substr(0, index));
  tokens.emplace_back(view.substr(index + 1));
  return tokens;
}
```

<details>
   <summary>Solution</summary>

```cpp
inline std::vector<std::string> split(std::string_view view, char delimiter) {
  std::vector<std::string> tokens;

  auto start = view.begin();
  const auto stop = view.end();

  auto is_delimiter = [delimiter](char c) { return c == delimiter; };

  while (start < stop) {
    auto start_word = std::find_if_not(start, stop, is_delimiter);
    auto end_word = std::find_if(start_word, stop, is_delimiter);
    tokens.emplace_back(start_word, end_word);
    start = end_word;
  }

  return tokens;
}
```

</details>

## [Exercise 415][1]

### Get int from string in [StringView.hpp][8]

```cpp
inline int to_int(std::string_view /*word*/) {
  int value{};
  // Exercise 415 : Get int from string
  return value;
}
```

<details>
   <summary>Solution</summary>

```cpp
inline int to_int(std::string_view word) {
  int value{};
  std::from_chars(word.data(), word.data() + word.size(), value);
  return value;
}
```

</details>

[1]: 41_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/string/basic_string_view/basic_string_view
[3]: https://en.cppreference.com/w/cpp/string/byte/toupper
[4]: https://en.cppreference.com/w/cpp/algorithm/transform
[5]: ../benchmarks/line_stream_benchmark.cpp
[6]: ../../lib/include/LineViewStream.hpp
[7]: ../../lib/include/LineStream.hpp
[8]: ../../lib/include/StringView.hpp

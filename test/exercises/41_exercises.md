[< Back](README.md)

# 41. std::string_view and std::span

* [Exercise 410](#exercise-410)
* [Exercise 411](#exercise-411)
* [Exercise 412](#exercise-412)
* [Exercise 413](#exercise-413)

## Exercise 410

### Implement next() in LineViewStream.hpp

Uncomment this line in the benchmark test/benchmarks/line_stream_benchmark.cpp

```cpp
    // REQUIRE(lines == 1950);
```

Implement the next function in LineViewStream.hpp trying not to make copies of 
the string except in the return statement.

Compare the performance with LineStream.hpp by running the benchmark in
line_stream_benchmark.cpp.

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

## [Exercise 411][1]

### Make whole std::string_view uppercase

<details>
   <summary>Solution</summary>

```cpp
inline std::string to_upper(std::string_view word) {
  std::string ret;
  ret.reserve(word.size());
  std::transform(word.begin(), word.end(), std::back_inserter(ret), ::toupper);
  return ret;
}
```

Windows

```cpp
inline std::string to_upper(std::string_view word) {
  std::string ret;
  ret.reserve(word.size());
  std::transform(word.begin(), word.end(), std::back_inserter(ret), [](int c) -> char { return static_cast<char>(::toupper(c)); });
  return ret;
}
```

</details>

## [Exercise 412][1]

### Trim leading and trailing white space from std::string_view

* [std::string_view][2]

```cpp
inline std::string trim(std::string_view /*view*/) {
  // Exercise 412 : Trim leading and trailing white space
  return {};
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

### Split std::string_view into tokens based on whitespace

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

### Split view into tokens based on delimiter

<details>
   <summary>Solution</summary>

```cpp
inline std::vector<std::string> split(std::string_view view, char delimiter) {
  std::vector<std::string> tokens;

  auto start = view.begin();
  const auto stop = view.end();

  auto is_comma = [delimiter](char c) { return c == delimiter; };

  while (start < stop) {
    auto start_word = std::find_if_not(start, stop, is_comma);
    auto end_word = std::find_if(start_word, stop, is_comma);
    tokens.emplace_back(start_word, end_word);
    start = end_word;
  }

  return tokens;
}
```

</details>

## [Exercise 415][1]

### Get int from string

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

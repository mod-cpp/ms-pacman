[< Back](README.md)

# 42. std::string_view and std::span

* [Exercise 420](#exercise-420)
* [Exercise 421](#exercise-421)
* [Exercise 422](#exercise-422)
* [Exercise 423](#exercise-423)

## Exercise 420

### Implement next() in LineViewStream.hpp

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

## [Exercise 421][1]

### Make whole word uppercase

<details>
   <summary>Solution</summary>

```cpp
std::string to_upper(std::string_view word) {
  std::string ret;
  ret.resize(word.size());
  std::transform(word.begin(), word.end(), ret.begin(), ::toupper);
  return ret;
}
```

</details>

## [Exercise 422][1]

### Trim leading and trailing white space in StringView.hpp

* [std::string_view][2]

```cpp
std::string trim(std::string_view /*view*/) {
  // Exercise 422 : Trim leading and trailing white space
  return {};
}
```

<details>
   <summary>Solution</summary>

```cpp
std::string trim(std::string_view view) {
  auto start_it = std::find_if_not(view.begin(), view.end(), ::isspace);
  auto end_it = std::find_if_not(view.rbegin(), view.rend(), ::isspace);
  return std::string{ start_it, end_it.base() };
}
```

</details>

## [Exercise 423][1]

### Split view into tokens based on whitespace

<details>
   <summary>Solution</summary>

```cpp
std::vector<std::string> split(std::string_view view) {
  std::vector<std::string> tokens;

  auto start = view.begin();
  const auto stop = view.end();

  while (start < stop) {
    auto start_word = std::find_if_not(start, stop, ::isspace);
    auto end_word = std::find_if(start_word, stop, ::isspace);
    auto dist = std::distance(start_word, end_word);
    tokens.emplace_back(start_word, dist);
    start = end_word;
  }

  return tokens;
}
```

</details>

[1]: 42_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/string/basic_string_view/basic_string_view

[< Back](README.md)

# 46. Pragmatic introduction to move semantics and return value optimizations

* [Exercise 460](#exercise-460)
* [Exercise 461](#exercise-461)

## Exercise 460
### Refactor HighScoreFile.hpp

* Use fstream instead, as shown on the slide

<details>
   <summary>Solution</summary>

```cpp
#include <fstream>
#include <sstream>

class HighScoreFile final {
public:
 explicit HighScoreFile(std::string name)
     : filename(std::move(name)),
       file(filename.c_str()) {
   };


 std::string read_all() {
   std::stringstream buffer;
   buffer << file.rdbuf();
   return buffer.str();
 }

 bool is_valid() const { return file.is_open(); }

private:
 std::string filename;
 std::basic_fstream<char> file;
};
```

</details>

## [Exercise 461][1]
### Implement bounding_box

* cppreference : [std::min][2]
* cppreference : [std::max][3]
   
How could you make sure that return value optimization is performed (there may be multiple ways to do this)?

<details>
   <summary>Solution</summary>

Adding a constructor and deleting both the copy constructor and the move constructor let you enforce that RVO is performed.
You could also look at the generated assembly.

```cpp
struct Rect {
  Rect(Point point, Size size)
    : point(point),
      size(size) {}
  Rect(const Rect&) = delete;
  Rect(Rect&&)      = delete;
  size_t width() const { return size.width; }
  size_t height() const { return size.height; }
  int x() const { return point.x; }
  int y() const { return point.y; }
  int right() const { return point.x + int(size.width); }
  int bottom() const { return point.y + int(size.height); }

  Point point;
  Size size;
};

static Rect bounding_box(const Rect & one, const Rect & two) {
  int x = std::min(one.x(), two.x());
  int y = std::min(one.y(), two.y());
  int right = std::max(one.right(), two.right());
  int bottom = std::max(one.bottom(), two.bottom());
  auto width = static_cast<size_t>(right - x);
  auto height = static_cast<size_t>(bottom - y);
  return { { x, y }, { width, height } };
}
```

</details>

[1]: 46_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/algorithm/min
[3]: https://en.cppreference.com/w/cpp/algorithm/max

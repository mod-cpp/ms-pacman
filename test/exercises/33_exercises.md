[< Back](README.md)

# 33. Operators

## Exercise 330: 

## [Exercise 331][1] : operator== as a free function

<details>
   <summary>Solution</summary>

```cpp
bool operator==( const Point& lhs, const Point& rhs ) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

// Comment out define below
//#define ENABLE_TEST_331
TEST_CASE("Exercise 331 : operator== as a free function", "[33]") {
  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_331
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_331
  CHECK(p != other);
#endif
}
```
</details>

## [Exercise 332][1] : operator== as a defaulted member function

<details>
   <summary>Solution</summary>

```cpp
//#define ENABLE_TEST_332
TEST_CASE("Exercise 332 : operator== as a defaulted member function", "[33]") {
  struct Point {
    int x = 0;
    int y = 0;
    bool operator==(const Point & other) const = default;
  };

  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_332
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_332
  CHECK(p != other);
#endif
}
```
</details>

## [Exercise 333][1] : operator== as a custom member function

<details>
   <summary>Solution</summary>

```cpp
//#define ENABLE_TEST_333
TEST_CASE("Exercise 333 : operator== as a custom member function", "[33]") {
  struct Point {
    int x = 0;
    int y = 0;
    bool operator==(const Point & other) const {
      return x == other.x && y == other.y;
    }
  };

  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_333
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_333
  CHECK(p != other);
#endif
}
```
</details>

## [Exercise 334][1] : operator<=> as a free function

<details>
   <summary>Solution</summary>

```cpp

```
</details>

## [Exercise 335][1] : operator<=> as a defaulted member function

<details>
   <summary>Solution</summary>

```cpp

```
</details>

## [Exercise 336][1] : operator<=> as a custom member function

<details>
   <summary>Solution</summary>

```cpp

```
</details>

## [Exercise 337][1] : operator() as a custom member function

<details>
   <summary>Solution</summary>

```cpp

```
</details>

[1]: 33_exercises.cpp

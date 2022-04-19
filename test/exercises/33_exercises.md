[< Back](README.md)

# 33. Operators

## Exercise 330: 

## [Exercise 331][1] : operator== as a free function

* cppreference : [Comparison Operators][2]
* cppreference : [Two-Way Comparison][5]

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

* cppreference : [Comparison Operators][2]
* cppreference : [Two-Way Comparison][5]

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

* cppreference : [Comparison Operators][2]
* cppreference : [Two-Way Comparison][5]

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

* cppreference : [Comparison Operators][2]
* cppreference : [Three-Way Comparison][4]

<details>
   <summary>Solution</summary>

```cpp
bool operator==( const Point& lhs, const Point& rhs ) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::strong_ordering operator<=>( const Point& lhs, const Point& rhs ) {
  if (auto C = lhs.x <=> rhs.x; C != 0)
    return C;
  return lhs.y <=> rhs.y;
}
```
</details>

## [Exercise 335][1] : operator<=> as a defaulted member function

* cppreference : [Comparison Operators][2]
* cppreference : [Three-Way Comparison][4]

<details>
   <summary>Solution</summary>

```cpp
//#define ENABLE_TEST_335
TEST_CASE("Exercise 335 : operator<=> as a defaulted member function", "[33]") {
  struct Point {
    int x = 0;
    int y = 0;
    auto operator<=>(const Point& other) const = default;
  };

  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_335
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_335
  CHECK(p != other);
  CHECK(p <= other);
#endif
}
```
</details>

## [Exercise 336][1] : operator<=> as a custom member function

* cppreference : [Comparison Operators][2]
* cppreference : [Three-Way Comparison][4]

<details>
   <summary>Solution</summary>

```cpp
//#define ENABLE_TEST_336
TEST_CASE("Exercise 336 : operator<=> as a custom member function", "[33]") {
  struct Point {
    int x = 0;
    int y = 0;
    std::strong_ordering operator<=>(const Point& other) const {
      if (auto C = x <=> other.x; C != 0)
        return C;
      return y <=> other.y;
    }
    bool operator==(const Point& other) const = default;
  };

  Point p;
  CHECK(p.x == 0);
#ifndef ENABLE_TEST_336
  CHECK(p == p);
#endif

  Point other{ 1, 1 };
  CHECK(other.x == 1);
#ifndef ENABLE_TEST_336
  CHECK(p != other);
  CHECK(p <= other);
#endif
}
```
</details>

## [Exercise 337][1] : operator() as a custom member function

* cppreference : [Function Call Operator][3]

<details>
   <summary>Solution</summary>

```cpp
TEST_CASE("Exercise 337 : operator() as a custom member function", "[33]") {
  struct OrigoVisitor {
    constexpr auto operator()(const Point & p) const { return p.x == 0 && p.y == 0; }
  };

  OrigoVisitor visit;
  Point p;
  CHECK(visit(p));

  Point other{ 1, 1 };
  CHECK(!visit(other));
}
```
</details>

[1]: 33_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/language/operators#Comparison_operators
[3]: https://en.cppreference.com/w/cpp/language/operators#Function_call_operator
[4]: https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
[5]: https://en.cppreference.com/w/cpp/language/operator_comparison#Two-way_comparison

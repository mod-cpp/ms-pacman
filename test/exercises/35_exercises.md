[< Back](README.md)

# 35. Aliases and alias templates

## Exercise 350:

## [Exercise 351][1] : using alias int_set

* cppreference : [Type alias, alias template][3]

<details>
   <summary>Solution</summary>

```cpp
using int_set = set<int>;
```
</details>

## [Exercise 352][1] : Implement array2d (alias template)

* cppreference : [std::array][2]
* cppreference : [Type alias, alias template][3]

<details>
   <summary>Solution</summary>

```cpp
template<typename T, auto Width, auto Height>
using array2d = std::array<std::array<T, Width>, Height>;
```
</details>

[1]: 35_exercises.cpp
[2]: https://en.cppreference.com/w/cpp/container/array
[3]: https://en.cppreference.com/w/cpp/language/type_alias

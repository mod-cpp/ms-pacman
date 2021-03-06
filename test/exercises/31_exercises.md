[< Back](README.md)

# 31. Introduction

* [Exercise 310](#exercise-310)
* [Exercise 311](#exercise-311)
* [Exercise 312](#exercise-312)

## Exercise 310
### Set up development environment

### Install tools

#### All Platforms

* Follow the instructions to install VSCode from https://code.visualstudio.com/
* If you already have it installed, make sure it is up-to-date

#### Ubuntu 20.04 or newer

* Install the build tools
```bash
sudo apt-get install ninja-build pkg-config curl zip unzip tar cmake build-essential libx11-dev libxrandr-dev libxi-dev libudev-dev libgl1-mesa-dev clang-12 g++-10
```

#### Fedora 33 or newer

* Install the build tools
```bash
sudo dnf install ninja-build SFML-devel libXi-devel libX11-devel libXrandr-devel mesa-libGL-devel systemd-devel
```

#### Arch Linux

If there are opengl driver errors, try running in software mode

#### FreeBSD 12 or newer

* Install the build tools
```bash
sudo pkg install catch cmake libfmt ninja sfml
```

**After installing the build tools, you may have to reboot your IDE and/or your Linux
session if you encounter any errors such as Ninja not being found by VScode**.

#### Windows:

* Follow the instructions to install cmake (3.22) from https://cmake.org/download/
* Install Visual Studio 2022 https://visualstudio.microsoft.com/
* Reboot your computer once that's done.
* If you have issues with using VSCode, start it from the "Developer Command Prompt for VS 2022"

#### Mac

* Install clang by typing `xcode-select --install` in a terminal and following the instructions
* Install the build tools
```bash
brew install cmake ninja
```
* Follow the instructions for [Launching VSCode from the command line](https://code.visualstudio.com/docs/setup/mac#_launching-from-the-command-line)

### Configure and build project

#### All Platforms, using VS Code

```bash
git clone https://github.com/mod-cpp/ms-pacman.git
cd ms-pacman
code .
```

* You will get a popup in the lower right hand corner asking "Do you want to install the recommended extensions for C++?" - click Install

#### Commandline based build (Not used in this training)

```bash
git clone https://github.com/mod-cpp/ms-pacman.git
cd ms-pacman
cmake -B build
cmake --build build
ctest --test-dir build -C Debug
```

#### Using CLion

* When opening the project in CLion use the CMake preset for your platform - see popup in the lower right hand corner
* Unselect the "Debug" profile
* Select for example the preset profile called "windows-build" if you are on Windows
* Enable it by checking the checkbox "Enable profile"
* Click "Apply" and "OK"
* (If CLion created a `cmake-build-debug` folder you can safely delete it, we will be using the `build` directory)

## [Exercise 311][1]
### Enable a test and make it green

* Catch2 : [Special Tags][3]

<details>
   <summary>Solution</summary>

```cpp
TEST_CASE("Exercise 311 : Enable a test and make it green", "[31]") {
  REQUIRE(true == true);
}
```
</details>

## [Exercise 312][1]
### Make both asserts run (distinguish between REQUIRE and CHECK in Catch2)

* Catch2 : [Assertion Macros][2]

<details>
   <summary>Solution</summary>

```cpp
TEST_CASE("Exercise 312 : Make both asserts run (distinguish between REQUIRE and CHECK in Catch2)", "[31]") {
  CHECK(true == true);
  CHECK(true == true);
}
```
</details>

[1]: 31_exercises.cpp
[2]: https://github.com/catchorg/Catch2/blob/v2.x/docs/assertions.md
[3]: https://github.com/catchorg/Catch2/blob/v2.x/docs/test-cases-and-sections.md#special-tags

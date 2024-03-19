#!/bin/bash
set -e

# cmake --preset Linux -DCMAKE_BUILD_TYPE=Debug # configure
# cmake --build --preset Linux-Build --config Debug # build
# ctest --preset Linux-Test -C Debug # run tests

# Install up-to-date CMake (https://apt.kitware.com/)
CODE_NAME=`lsb_release -cs`
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null
echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ ${CODE_NAME} main" | sudo tee /etc/apt/sources.list.d/kitware.list >/dev/null
sudo apt-get update
sudo apt-get install kitware-archive-keyring
sudo apt-get install cmake

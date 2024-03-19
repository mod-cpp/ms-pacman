#!/bin/bash
set -e

#  sudo apt install curl
#  DEBIAN_FRONTEND=noninteractive bash <(curl -s https://raw.githubusercontent.com/mod-cpp/ms-pacman/main/dev/ubuntu.sh)

# 0) List WSLs    wsl -l                                    (In Terminal)
# 1) Remove old   wsl --unregister Ubuntu-20.04             (OPTIONAL)
# 2) Install      wsl --install --distribution Ubuntu-20.04 (Close window)
# 3) Run          wsl -d Ubuntu-20.04                       (In Terminal)
# 4) Script       ./ubuntu.sh                               (Ctrl+D)
# 5) Terminate    wsl -t Ubuntu-20.04                       (In Terminal)
# 6) Run          wsl -d Ubuntu-20.04                       (In Terminal)
# 7) Run CMake
# 8) Build clean

info() {
  echo -e "\x1B[36m\nMod(C++) Intermediate : $1\x1B[0m"
}

instruction() {
  echo -e "\x1B[33m$1\x1B[0m"
}

if grep -qi microsoft /proc/version; then
  info "[WSL] Windows Subsystem for Linux detected"
  RUNNING_ON_WSL=1
else
  info "[Native-Ubuntu] Windows Subsystem for Linux NOT detected"
  RUNNING_ON_WSL=0
fi

info "Update Ubuntu"
sudo apt update -y
sudo apt upgrade -y

if test $RUNNING_ON_WSL -eq 1
then
  info "[WSL] Make wsl.conf file"
  sudo echo -e "[automount]\noptions = \"metadata\"\nenabled = true\n" | sudo tee /etc/wsl.conf >/dev/null
fi

if test $RUNNING_ON_WSL -eq 0
then
  info "[Native-Ubuntu] Install VSCode from Microsoft"
  # install VSCode according to https://code.visualstudio.com/docs/setup/linux
  sudo apt-get install -y wget gpg
  wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
  sudo install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
  sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
  rm -f packages.microsoft.gpg
  sudo apt install -y apt-transport-https
  sudo apt update
  sudo apt install -y code
fi

# MsPacMan deps
sudo apt install -y \
build-essential \
cmake \
g++-10 \
git \
libgl1-mesa-dev \
libudev-dev \
libx11-dev \
libxi-dev \
libxrandr-dev \
ninja-build \
pkg-config \
tar \
unzip \
zip

sudo apt install -y autoconf libtool
sudo apt install -y mesa-common-dev libglu1-mesa-dev libfreetype6-dev libopenal-dev libsndfile1-dev

info "Install CMake from Kitware"
# Install up-to-date CMake (https://apt.kitware.com/)
CODE_NAME=`lsb_release -cs`
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null
echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ ${CODE_NAME} main" | sudo tee /etc/apt/sources.list.d/kitware.list >/dev/null
sudo apt-get update
sudo apt-get install -y kitware-archive-keyring
sudo apt-get install -y cmake

info "Install Clang if it is possible"
# Install Clang last since it isn't strictly needed
sudo apt install -y clang
sudo apt install -y clang-12

info "MsPacMan development environment install done"

info "Next steps:"

instruction "git clone https://github.com/mod-cpp/ms-pacman.git"
instruction "cd ms-pacman/"
instruction "code ."

info "In VSCode install the recommended plugins"
info "In the left panel click on the CMake icon"
info "Edit the configure target and select 'linux-gcc'"
info "Wait..."

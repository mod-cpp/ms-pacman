#include "windows.h"
#include <string>

namespace ms_pacman {

std::string userlogin() {
  unsigned long size = 0;
  GetUserNameA(nullptr, &size);
  if (size == 0)
    return {};
  std::string s(size, 0);
  GetUserNameA(s.data(), &size);
  s.resize(size - 1);
  return s;
}

} // namespace ms_pacman

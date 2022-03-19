#include "User.hpp"
#include "unistd.h"

namespace ms_pacman {
std::string userlogin() {
  return getlogin();
}
} // namespace ms_pacman

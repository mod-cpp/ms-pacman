#include "User.hpp"
#include "unistd.h"

namespace ms_pacman {
std::string userlogin() {
  char * login = getlogin();
  return login ? login : "";
}
} // namespace ms_pacman

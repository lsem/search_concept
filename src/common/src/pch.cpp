#include <common/pch.h>

#include <cstdlib>

void sskit_unreachable(string what) {
  std::cerr << "Unreachable code: " << what << std::endl;
  std::abort();
}

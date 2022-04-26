#include "StdLogger.h"

#include <iostream>

void StdLogger::error(const std::string& msg) const {
  std::cerr << msg << std::endl;
}

void StdLogger::info(const std::string& msg) const {
  std::cout << msg << std::endl;
}

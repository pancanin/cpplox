#include "StdLogger.h"

#include <iostream>

void StdLogger::error(const std::string& msg) const {
  std::cerr << msg << std::endl;
}

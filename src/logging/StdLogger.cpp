#include "StdLogger.h"

#include <iostream>

void StdLogger::error(const std::string& msg) const {
  std::cerr << msg;
}

void StdLogger::info(const std::string& msg, bool insertNewLine) const {
	std::cout << msg << (insertNewLine ? "\n" : "");
}

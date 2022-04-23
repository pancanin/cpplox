#include "Main.h"

#include <iostream>
#include <fstream>

void Main::runFile(const std::string& fileName) const {
  std::ifstream ifs(fileName);
  std::string sourceCode((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  run(sourceCode);
}

void Main::runREPL() const {
  for (;;) {
    std::cout << "> ";
    std::string command;
    std::cin >> command;
    run(command);
  }
}

void Main::run(const std::string& sourceCode) const {
  std::cout << sourceCode << std::endl;
}

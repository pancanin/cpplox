#include "Main.h"

#include <iostream>
#include <fstream>

Main::Main(Logger& logger): logger(logger), errored(false) {}

void Main::runFile(const std::string& fileName) const {
  std::ifstream ifs(fileName);
  std::string sourceCode((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  run(sourceCode);
}

void Main::runREPL() {
  for (;;) {
    std::cout << "> ";
    std::string command;
    std::cin >> command;
    run(command);
    errored = false;
  }
}

void Main::run(const std::string& sourceCode) const {
  std::cout << sourceCode << std::endl;
}

void Main::error(int32_t line, const std::string& msg) {
  report(line, "", msg);
  errored = true;
}

void Main::report(int32_t line, const std::string& where, const std::string& msg) const {
  std::cout << "[[line " << line << "]] Error: " << where << ": " << msg << std::endl;
}

bool Main::hasError() const {
  return errored;
}

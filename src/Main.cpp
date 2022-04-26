#include "Main.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "src/scanner/Scanner.h"
#include "src/scanner/Token.h"
#include "src/logging/Logger.h"
#include "src/logging/LangErrorLogger.h"

Main::Main(Logger& logger, LangErrorLogger& langErrorLogger): logger(logger), langErrorLogger(langErrorLogger) {}

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

    langErrorLogger.clearError();
  }
}

void Main::run(const std::string& sourceCode) const {
  Scanner scanner(sourceCode);

  std::vector<Token> tokens = scanner.scanTokens();

  for (Token t : tokens) {
    std::cout << t << std::endl;
  }

}

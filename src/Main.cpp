#include "Main.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "src/scanner/Scanner.h"
#include "src/scanner/Token.h"

#include "src/logging/Logger.h"
#include "src/logging/LangErrorLogger.h"

#include "src/parser/Parser.h"

#include "src/syntax/AstPrinter.h"

#include "src/interpreter/Interpreter.h"

Main::Main(Logger& logger, LangErrorLogger& langErrorLogger): logger(logger), langErrorLogger(langErrorLogger) {}

void Main::runFile(const std::string& fileName) const {
  std::ifstream ifs(fileName);
  std::string sourceCode((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  run(sourceCode);
}

void Main::runREPL() {
  for (;;) {
    logger.info("> ", false);

    std::string command;
    getline(std::cin, command);

    run(command);

    langErrorLogger.clearError();
  }
}

void Main::run(const std::string& sourceCode) const {
  Scanner scanner(sourceCode, langErrorLogger);
  std::vector<Token> tokens = scanner.scanTokens();
  Parser parser(tokens, langErrorLogger);
  Expr* expr = parser.parse();
  Interpreter interpreter(logger, langErrorLogger);


  if (langErrorLogger.hasError()) return;

  interpreter.interpret(*expr);

  AstPrinter printer;

  logger.info(printer.print(*expr));
}

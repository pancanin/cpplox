#include "Main.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <signal.h>
//#include <windows.h>

#include "src/scanner/Scanner.h"
#include "src/scanner/Token.h"

#include "src/logging/Logger.h"
#include "src/logging/LangErrorLogger.h"

#include "src/parser/Parser.h"

#include "src/syntax/AstPrinter.h"

#include "src/interpreter/Interpreter.h"
#include "src/syntax/Statement.h"

static void signal_callback_handler(int signum) {
    exit(signum);
}

//BOOL WINAPI consoleHandler(DWORD signal) {
//
//    if (signal == CTRL_C_EVENT)
//        printf("Ctrl-C handled\n"); // do cleanup
//
//    return TRUE;
//}

Main::Main(Logger& logger, LangErrorLogger& langErrorLogger): logger(logger), langErrorLogger(langErrorLogger), env(std::make_shared<Environment>()) {}

void Main::runFile(const std::string& fileName) const {
  std::ifstream ifs(fileName);
  std::string sourceCode((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  run(sourceCode);

  env->clear();
}

void Main::runREPL() {
  signal(SIGINT, signal_callback_handler);

  /*if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
    logger.error("Could not set control handler. Ctrl + * won't work, so you'd have to forcefully close the console.\n");
  }*/

  for (;;) {
    logger.info("> ", false);

    std::string command;
    getline(std::cin, command);

    if (command.empty()) {
      continue;
    }

    run(command);

    langErrorLogger.clearError();
  }

  env->clear();
}

void Main::run(const std::string& sourceCode) const {
  Scanner scanner(sourceCode, langErrorLogger);
  std::vector<Token> tokens = scanner.scanTokens();
  Parser parser(tokens, langErrorLogger);
  auto statements = parser.parse();
  Interpreter interpreter(logger, langErrorLogger, env);

  if (langErrorLogger.hasError()) return;

  interpreter.interpret(statements);
}

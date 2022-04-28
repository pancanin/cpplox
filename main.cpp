#include <iostream>

#include <cstdint>
#include <string>

#include "src/logging/StdLogger.h"
#include "src/Main.h"

#include "src/logging/StdLogger.h"
#include "src/logging/LangErrorLogger.h"

int32_t main(int32_t argc, char **argv) {
  const int32_t INVALID_COMMAND_CODE = 64;
  StdLogger stdLogger;
  LangErrorLogger errorLogger(stdLogger);
  Main main(stdLogger, errorLogger);

  if (argc > 2) {
    stdLogger.info("Correct usage: cpplox [script] or just cpplox for REPL");

    return INVALID_COMMAND_CODE;
  } else if (argc == 2) {
    std::string fileName(argv[1]);

    main.runFile(fileName);

    if (errorLogger.hasError()) {
      return INVALID_COMMAND_CODE;
    }
  } else {
    main.runREPL();
  }

  return 0;
}

#include <iostream>

#include <cstdint>
#include <string>

#include "src/logging/StdLogger.h"
#include "src/Main.h"

#include "src/logging/StdLogger.h"

int32_t main(int32_t argc, char **argv) {
  const int32_t INVALID_COMMAND_CODE = 64;
  StdLogger stdLogger;
  Main main(stdLogger);

  if (argc > 2) {
    std::cout << "Correct usage: cpplox [script] or just cpplox for REPL" << std::endl;

    return INVALID_COMMAND_CODE;
  } else if (argc == 2) {
    std::string fileName(argv[1]);

    main.runFile(fileName);

    if (main.hasError()) {
      return INVALID_COMMAND_CODE;
    }
  } else {
    main.runREPL();
  }

  return 0;
}

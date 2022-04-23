#include <iostream>

#include <cstdint>
#include <string>

#include "src/Main.h"

int32_t main(int32_t argc, char **argv) {
  Main main;



  if (argc > 2) {
    std::cout << "Correct usage: cpplox [script] or just cpplox for REPL" << std::endl;

    return 64;
  } else if (argc == 2) {
    std::string fileName(argv[1]);
    std::cout << "Filename is " << fileName << std::endl;
    main.runFile(fileName);
  } else {
    main.runREPL();
  }

  return 0;
}

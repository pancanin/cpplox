#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <string>
#include <cstdint>
#include <memory>

#include "src/logging/LangErrorLogger.h"
#include "src/logging/Logger.h"
#include "src/env/Environment.h"

class Main {
public:
  Main(Logger&, LangErrorLogger&);
  void runFile(const std::string& fileName) const;
  void runREPL();
private:
  Logger& logger;
  LangErrorLogger& langErrorLogger;
  std::shared_ptr<Environment> env;

  void run(const std::string& sourceCode) const;
};

#endif /* SRC_MAIN_H_ */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <string>
#include <cstdint>

#include "src/logging/Logger.h"

class Main {
public:
  Main(Logger&);
  void runFile(const std::string& fileName) const;
  void runREPL();

  void error(int32_t line, const std::string& msg);
  void report(int32_t line, const std::string& where, const std::string& msg) const;

  bool hasError() const;
private:
  Logger& logger;
  bool errored;

  void run(const std::string& sourceCode) const;
};

#endif /* SRC_MAIN_H_ */

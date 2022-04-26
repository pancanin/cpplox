#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <string>
#include <cstdint>

struct Logger;
struct LangErrorLogger;

class Main {
public:
  Main(Logger&, LangErrorLogger&);
  void runFile(const std::string& fileName) const;
  void runREPL();
private:
  Logger& logger;
  LangErrorLogger& langErrorLogger;

  void run(const std::string& sourceCode) const;
};

#endif /* SRC_MAIN_H_ */

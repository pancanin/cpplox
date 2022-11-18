#ifndef SRC_LOGGING_LANGERRORLOGGER_H_
#define SRC_LOGGING_LANGERRORLOGGER_H_

#include <cstdint>
#include <string>

#include "src/scanner/Token.h"
#include "src/logging/Logger.h"

class LangErrorLogger {
public:
  LangErrorLogger(Logger&);

  void error(int32_t line, const std::string& msg);
  void error(Token token, std::string msg);
  void report(int32_t line, const std::string& where, const std::string& msg) const;
  bool hasError() const;
  void clearError();
private:
  Logger& logger;
  bool errored;
};

#endif /* SRC_LOGGING_LANGERRORLOGGER_H_ */

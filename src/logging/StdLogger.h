#ifndef SRC_LOGGING_STDLOGGER_H_
#define SRC_LOGGING_STDLOGGER_H_

#include "Logger.h"

class StdLogger : public Logger {
public:
  ~StdLogger() = default;
  void error(const std::string& msg) const;
  void info(const std::string& msg) const;
};

#endif /* SRC_LOGGING_STDLOGGER_H_ */

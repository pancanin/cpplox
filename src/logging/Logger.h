#ifndef SRC_LOGGING_LOGGER_H_
#define SRC_LOGGING_LOGGER_H_

#include <string>

class Logger {
public:
  virtual ~Logger() = default;
  virtual void error(const std::string& msg) const = 0;
};

#endif /* SRC_LOGGING_LOGGER_H_ */

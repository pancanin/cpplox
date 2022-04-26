#include "LangErrorLogger.h"

#include "src/logging/Logger.h"

LangErrorLogger::LangErrorLogger(Logger& logger): logger(logger), errored(false) {}

bool LangErrorLogger::hasError() const {
  return errored;
}

void LangErrorLogger::error(int32_t line, const std::string& msg) {
  report(line, "", msg);
  errored = true;
}

void LangErrorLogger::report(int32_t line, const std::string& where, const std::string& msg) const {
  logger.error("[[line " + std::to_string(line) + "]] Error: " + where + ": " + msg);
}

void LangErrorLogger::clearError() {
  errored = false;
}

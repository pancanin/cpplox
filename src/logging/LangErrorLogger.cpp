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
  logger.error("[[line " + std::to_string(line) + "]] Error " + where + ": " + msg);
}

void LangErrorLogger::clearError() {
  errored = false;
}

void LangErrorLogger::error(Token token, std::string msg) {
	if (token.type == TokenType::EOFILE) {
		report(token.line, "end of file", msg);
	} else {
		report(token.line, "at token " + token.lexeme + " and column " + std::to_string(token.lineOffset), msg);
	}
}

// The above error reporting is not great...We can use information about at what offset from the beginning of source code 
// the token is so that we can exert a snippet from the code around where the error is and mark the place where the invalid expression is.
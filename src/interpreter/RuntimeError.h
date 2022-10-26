#ifndef SRC_INTERPRETER_RUNTIMEERROR_H_
#define SRC_INTERPRETER_RUNTIMEERROR_H_

#include <stdexcept>
#include <string>

#include "src/scanner/Token.h"

class RuntimeError : public std::runtime_error {
public:
  RuntimeError(Token token, const std::string& msg): token(token), std::runtime_error(msg) {}

  char const* what() const throw() {
    return std::runtime_error::what();
  }

  Token token;
};


#endif /* SRC_INTERPRETER_RUNTIMEERROR_H_ */

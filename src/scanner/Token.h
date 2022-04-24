#ifndef SRC_SCANNER_TOKEN_H_
#define SRC_SCANNER_TOKEN_H_

#include <string>
#include <cstdint>
#include <iostream>

#include "src/scanner/TokenType.h"

class Token {
  Token(TokenType type, const std::string& lexeme, const std::string& literal, int32_t line);

  friend std::ostream& operator<<(std::ostream& os, const Token&) const;
private:
  TokenType type;
  std::string lexeme;
  std::string literal;
  int32_t line;
};

#endif /* SRC_SCANNER_TOKEN_H_ */

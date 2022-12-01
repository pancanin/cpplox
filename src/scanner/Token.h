#ifndef SRC_SCANNER_TOKEN_H_
#define SRC_SCANNER_TOKEN_H_

#include <string>
#include <cstdint>
#include <iostream>

#include "src/scanner/TokenType.h"

class Token {
public:
  Token();
  Token(TokenType type, const std::string& lexeme, const std::string& literal, int32_t line, int32_t lineOffset);

  friend std::ostream& operator<<(std::ostream& os, const Token&);

  TokenType type;
  std::string lexeme;
  std::string literal;
  int32_t line;
  int32_t lineOffset;

  static const Token NULL_TOKEN;
};

#endif /* SRC_SCANNER_TOKEN_H_ */

#include "Token.h"

Token::Token(TokenType type, const std::string& lexeme, const std::string& literal, int32_t line):
  type(type),
  lexeme(lexeme),
  literal(literal),
  line(line) {}

std::ostream& operator<<(std::ostream& os, const Token& token) const {
  return os << token.type << " " << token.lexeme << " " << token.literal;
}

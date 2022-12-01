#include "Token.h"

Token::Token(TokenType type, const std::string& lexeme, const std::string& literal, int32_t line, int32_t lineOffset):
  type(type),
  lexeme(lexeme),
  literal(literal),
  line(line),
  lineOffset(lineOffset) {}

Token::Token(): Token(TokenType::NA, "", "", 1, 0) {}

std::ostream& operator<<(std::ostream& os, const Token& token) {
  return os << " " << token.lexeme << " " << token.literal;
}

// TODO: Change this to a method so we can set the line number and offset.
const Token Token::NULL_TOKEN(TokenType::NIL, "nil", "nil", 1, 0);

#include "Scanner.h"

#include "src/scanner/TokenType.h"

Scanner::Scanner(const std::string& source): source(source), start(0), current(0), line(1) {}

bool Scanner::isAtEnd() const {
  return current >= source.size();
}

const std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.emplace_back(TokenType::EOFILE, "", "", line);

  return tokens;
}

void Scanner::scanToken() {
  char c = advance();

  switch (c) {
    case '(': addToken(LEFT_PAREN); break;
    case ')': addToken(RIGHT_PAREN); break;
    case '{': addToken(LEFT_BRACE); break;
    case '}': addToken(RIGHT_BRACE); break;
    case ',': addToken(COMMA); break;
    case '.': addToken(DOT); break;
    case '-': addToken(MINUS); break;
    case '+': addToken(PLUS); break;
    case ';': addToken(SEMICOLON); break;
    case '*': addToken(STAR); break;
  }
}

char Scanner::advance() {
  return source.at(current++);
}

void Scanner::addToken(TokenType type) {
  addToken(type, "");
}
void Scanner::addToken(TokenType type, const std::string& literal) {
  std::string text = source.substr(start, current);
  tokens.emplace_back(type, text, literal, line);
}

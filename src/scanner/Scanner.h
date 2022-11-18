#ifndef SRC_SCANNER_SCANNER_H_
#define SRC_SCANNER_SCANNER_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "src/scanner/Token.h"
#include "src/logging/LangErrorLogger.h"

class Scanner {
public:
  Scanner(const std::string& source, LangErrorLogger&);

  const std::vector<Token> scanTokens();
  void scanToken();
private:
  LangErrorLogger& errorLogger;
  std::string source;
  int32_t start;
  int32_t current;
  int32_t line;
  int32_t lineOffset;
  std::vector<Token> tokens;
  static std::unordered_map<std::string, TokenType> keywords;

  bool isAtEnd() const;
  char advance();
  char peek();
  char peekNext();
  void addToken(TokenType type);
  void addToken(TokenType type, const std::string& literal);
  bool matchNextCharacter(char next);

  void consumeComments();
  void consumeString();
  void consumeNumber();
  void consumeIdentifier();

  bool isDigit(char c) const;
  bool isAlpha(char c) const;
  bool isAlphaNumeric(char c) const;
};

#endif /* SRC_SCANNER_SCANNER_H_ */

#ifndef SRC_SCANNER_SCANNER_H_
#define SRC_SCANNER_SCANNER_H_

#include <string>
#include <vector>

#include "src/scanner/Token.h"

struct LangErrorLogger;

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
  std::vector<Token> tokens;

  bool isAtEnd() const;
  char advance();
  char peek();
  void addToken(TokenType type);
  void addToken(TokenType type, const std::string& literal);
  bool matchNextCharacter(char next);

  void handleComments();
  void handleString();
  void handleNumber();

  bool isDigit(char c) const;
};

#endif /* SRC_SCANNER_SCANNER_H_ */

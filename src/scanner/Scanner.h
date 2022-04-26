#ifndef SRC_SCANNER_SCANNER_H_
#define SRC_SCANNER_SCANNER_H_

#include <string>
#include <vector>

#include "src/scanner/Token.h"

class Scanner {
public:
  Scanner(const std::string& source);

  const std::vector<Token> scanTokens();
  void scanToken();
private:
  std::string source;
  int32_t start;
  int32_t current;
  int32_t line;
  std::vector<Token> tokens;

  bool isAtEnd() const;
  char advance();
  void addToken(TokenType type);
  void addToken(TokenType type, const std::string& literal);
};

#endif /* SRC_SCANNER_SCANNER_H_ */

#ifndef SRC_SCANNER_SCANNER_H_
#define SRC_SCANNER_SCANNER_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "src/scanner/Token.h"
#include "src/logging/LangErrorLogger.h"

/// <summary>
/// Extracts all meaningful 'words' from the source code and keeps them in a list of Tokens.
/// </summary>
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

  /// <summary>
  /// Checks whether we have reached the end of the source code.
  /// </summary>
  /// <returns>True if we have reached the end and false if we haven't.</returns>
  bool isAtEnd() const;

  /// <summary>
  /// Moves the cursor to the next character in the source code.
  /// </summary>
  /// <returns>Returns the character before the move.</returns>
  char advance();

  /// <summary>
  /// Inspect the current character from the source code.
  /// </summary>
  /// <returns>The current character.</returns>
  char peek();
  char peekNext();
  void addToken(TokenType type);

  /// <summary>
  /// Extracts the token from source code after reaching its end and adds it to a collection of tokens.
  /// </summary>
  /// <param name="type">What type of token have we found?</param>
  /// <param name="literal">The literal string of the Token, i.e. "somename", "var", etc.</param>
  void addToken(TokenType type, const std::string& literal); // TODO: Inspect this method. Do we need to pass a literal if it's calculated inside?

  /// <summary>
  /// Checks the current character and if it is matching the provided argument 'next' it increments the cursor.
  /// Example usage for scanning comments:
  /// case '/': matchNextCharacter('/') ? consumeComments() : addToken(TokenType::SLASH); break;
  /// </summary>
  /// <param name="next">The character to match.</param>
  /// <returns>Do we have such a character as next token.</returns>
  bool matchNextCharacter(char next);

  /// <summary>
  /// Called when we have found start of a line comment. Consumes all characters until we move to the next line, i.e comment has ended.
  /// </summary>
  void consumeComments();
  void consumeString();
  void consumeNumber();
  void consumeIdentifier();

  bool isDigit(char c) const;
  bool isAlpha(char c) const;
  bool isAlphaNumeric(char c) const;
};

#endif /* SRC_SCANNER_SCANNER_H_ */

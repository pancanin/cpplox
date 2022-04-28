#include "Scanner.h"

#include "src/scanner/TokenType.h"
#include "src/logging/LangErrorLogger.h"

Scanner::Scanner(const std::string& source, LangErrorLogger& logger)
	: errorLogger(logger), source(source), start(0), current(0), line(1) {}

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
    case '!': addToken(matchNextCharacter('=') ? BANG_EQUAL : BANG); break;
    case '=': addToken(matchNextCharacter('=') ? EQUAL_EQUAL : EQUAL); break;
    case '>': addToken(matchNextCharacter('=') ? GREATER_EQUAL : GREATER); break;
    case '<': addToken(matchNextCharacter('=') ? LESS_EQUAL : LESS); break;
    case '/': matchNextCharacter('/') ? handleComments() : addToken(SLASH); break;
    case '"': handleString(); break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    	handleNumber(); break;
    case ' ':
    case '\t':
    case '\r':
    	break;
    case '\n':
    	line++;
    	break;
    default: errorLogger.error(line, "Unexpected token.");
  }
}

void Scanner::handleComments() {
	while (!isAtEnd() && peek() != '\n') {
		advance();
	}
}

void Scanner::handleString() {
	while (!isAtEnd() && peek() != '"') {
		if (peek() == '\n') line++;
		advance();
	}

	if (isAtEnd()) {
		errorLogger.error(line, "Unterminated string.");
		return;
	}

	advance(); // closing quote

	std::string val = source.substr(start + 1, current - start - 2);
	addToken(STRING, val);
}

void Scanner::handleNumber() {
	while (isDigit(peek())) advance();

	if (!isAtEnd() && peek() == '.') {
		advance();

		while (isDigit(peek())) advance();
	}

	std::string number = source.substr(start, current - start);
	addToken(NUMBER, number);
}

char Scanner::advance() {
  return source.at(current++);
}

char Scanner::peek() {
	return source[current];
}

bool Scanner::matchNextCharacter(char next) {
	if (isAtEnd()) return false;
	if (source[current] == next) {
		current++;
		return true;
	}

	return false;
}

void Scanner::addToken(TokenType type) {
  addToken(type, "");
}
void Scanner::addToken(TokenType type, const std::string& literal) {
  std::string text = source.substr(start, current - start);
  tokens.emplace_back(type, text, literal, line);
}

bool Scanner::isDigit(char c) const {
	return c >= '0' && c <= '9';
}

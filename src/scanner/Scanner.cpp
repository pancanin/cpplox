#include "Scanner.h"

#include "src/scanner/TokenType.h"
#include "src/logging/LangErrorLogger.h"

std::unordered_map<std::string, TokenType> Scanner::keywords = {
		{"and",    TokenType::AND},
		{"class",  TokenType::CLASS},
		{"else",   TokenType::ELSE},
		{"false",  TokenType::FALSE},
		{"for",    TokenType::FOR},
		{"fun",    TokenType::FUN},
		{"if",     TokenType::IF},
		{"nil",    TokenType::NIL},
		{"or",     TokenType::OR},
		{"print",  TokenType::PRINT},
		{"return", TokenType::RETURN},
		{"super",  TokenType::SUPER},
		{"this",   TokenType::THIS},
		{"true",   TokenType::TRUE},
		{"var",    TokenType::VAR},
		{"while",  TokenType::WHILE}
};

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
    case '(': addToken(TokenType::LEFT_PAREN, "("); break;
    case ')': addToken(TokenType::RIGHT_PAREN, ")"); break;
    case '{': addToken(TokenType::LEFT_BRACE, "{"); break;
    case '}': addToken(TokenType::RIGHT_BRACE, "}"); break;
    case ',': addToken(TokenType::COMMA, ","); break;
    case '.': addToken(TokenType::DOT, "."); break;
    case '-': addToken(TokenType::MINUS, "-"); break;
    case '+': addToken(TokenType::PLUS, "+"); break;
    case ';': addToken(TokenType::SEMICOLON, ";"); break;
    case '*': addToken(TokenType::STAR, "*"); break;
    case '!': addToken(matchNextCharacter('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
    case '=': addToken(matchNextCharacter('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
    case '>': addToken(matchNextCharacter('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
    case '<': addToken(matchNextCharacter('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
    case '/': matchNextCharacter('/') ? consumeComments() : addToken(TokenType::SLASH); break;
    case '"': consumeString(); break;
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
    	consumeNumber(); break;
    case ' ':
    case '\t':
    case '\r':
    	break;
    case '\n':
    	line++;
    	break;
    default:
    	if (isAlpha(c)) {
    		consumeIdentifier();
    	} else {
    		errorLogger.error(line, "Unexpected token.");
    	}
  }
}

void Scanner::consumeComments() {
	while (!isAtEnd() && peek() != '\n') {
		advance();
	}
}

void Scanner::consumeString() {
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
	addToken(TokenType::STRING, val);
}

void Scanner::consumeNumber() {
	while (isDigit(peek())) advance();

	if (!isAtEnd() && peek() == '.' && isDigit(peekNext())) {
		advance();

		while (isDigit(peek())) advance();
	}

	std::string number = source.substr(start, current - start);
	addToken(TokenType::NUMBER, number);
}

void Scanner::consumeIdentifier() {
	while (isAlphaNumeric(peek())) advance();

	std::string identifier = source.substr(start, current - start);

	TokenType type = TokenType::IDENTIFIER;

	if (keywords.find(identifier) != keywords.end()) {
		type = keywords[identifier];
	}

	addToken(type);
}

char Scanner::advance() {
  return source.at(current++);
}

char Scanner::peek() {
	return source[current];
}

char Scanner::peekNext() {
	if (current + 1 >= source.size()) return '\0';
	return source[current + 1];
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

bool Scanner::isAlpha(char c) const {
	return (c >= 'a' && c <= 'z') ||
	 (c >= 'A' && c <= 'Z') ||
		c == '_';
}

bool Scanner::isAlphaNumeric(char c) const {
	return isAlpha(c) || isDigit(c);
}

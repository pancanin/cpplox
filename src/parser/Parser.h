#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include <cstdint>
#include <initializer_list>
#include <vector>

#include "src/scanner/Token.h"
#include "src/scanner/TokenType.h"
#include "src/syntax/Expr.h"
#include "src/parser/ParseError.h"

struct LangErrorLogger;

class Parser {
public:
	Parser(std::vector<Token>&, LangErrorLogger&);

	Expr* parse();
private:
	std::vector<Token>& tokens;
	int32_t currentTokenIndex;
	LangErrorLogger& logger;

	Expr* expression();
	Expr* equality();
	Expr* comparison();
	Expr* term();
	Expr* factor();
	Expr* unary();
	Expr* primary();

	Token getPreviousToken() const;
	Token getCurrentToken() const;
	bool hasReachedEnd() const;
	Token advance();
	bool checkIfCurrentTokenIs(TokenType) const;
	bool match(std::initializer_list<TokenType>);
	Token consume(TokenType type, std::string msg);

	ParseError error(Token token, std::string msg);
};

#endif /* SRC_PARSER_PARSER_H_ */

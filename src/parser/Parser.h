#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include <cstdint>
#include <initializer_list>
#include <vector>

#include "src/scanner/Token.h"
#include "src/scanner/TokenType.h"
#include "src/syntax/Expr.h"

class Parser {
public:
	Parser(std::vector<Token>&);

private:
	std::vector<Token>& tokens;
	int32_t currentTokenIndex;

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
	void advance();
	bool checkIfCurrentTokenIs(TokenType) const;
	bool match(std::initializer_list<TokenType>);
};

#endif /* SRC_PARSER_PARSER_H_ */

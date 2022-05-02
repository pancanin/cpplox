#include "Parser.h"

#include "src/syntax/BinaryExpr.h"

Parser::Parser(std::vector<Token>& tokens): tokens(tokens), currentTokenIndex(0) {}

Expr* Parser::expression() {
	return equality();
}
Expr* Parser::equality() {
	Expr* left = comparison();

	while (match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL})) {
		Token op = getPreviousToken();
		Expr* right = comparison();
		left = new BinaryExpr(*left, op, *right);
	}

	return left;
}

Token Parser::getPreviousToken() const {
	return tokens.at(currentTokenIndex - 1);
}

Token Parser::getCurrentToken() const {
	return tokens.at(currentTokenIndex);
}

bool Parser::checkIfCurrentTokenIs(TokenType type) const {
	return getCurrentToken().type == type;
}

bool Parser::hasReachedEnd() const {
	return currentTokenIndex >= tokens.size();
}

bool Parser::match(std::initializer_list<TokenType> types) {
	for (TokenType t : types) {
		if (checkIfCurrentTokenIs(t)) {
			advance();
			return true;
		}
	}

	return false;
}

void Parser::advance() {
	currentTokenIndex++;
}

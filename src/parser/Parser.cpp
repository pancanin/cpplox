#include "Parser.h"

#include "src/syntax/BinaryExpr.h"
#include "src/syntax/UnaryExpr.h"
#include "src/syntax/GroupingExpr.h"
#include "src/syntax/LiteralExpr.h"

#include "src/logging/LangErrorLogger.h"

Parser::Parser(std::vector<Token>& tokens, LangErrorLogger& logger):
	tokens(tokens), currentTokenIndex(0), logger(logger) {}

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

Expr* Parser::comparison() {
	Expr* left = term();

	while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
		Token op = getPreviousToken();
		Expr* right = term();
		left = new BinaryExpr(*left, op, *right);
	}

	return left;
}

Expr* Parser::term() {
	Expr* left = factor();

	while (match({TokenType::PLUS, TokenType::MINUS})) {
		Token op = getPreviousToken();
		Expr* right = factor();
		left = new BinaryExpr(*left, op, *right);
	}

	return left;
}

Expr* Parser::factor() {
	Expr* left = unary();

	while (match({TokenType::STAR, TokenType::SLASH})) {
		Token op = getPreviousToken();
		Expr* right = unary();
		left = new BinaryExpr(*left, op, *right);
	}

	return left;
}

Expr* Parser::unary() {
	if (match({TokenType::BANG, TokenType::MINUS})) {
		Token op = getPreviousToken();
		Expr* right = unary();
		return new UnaryExpr(op, *right);
	}

	return primary();
}

Expr* Parser::primary() {
	if (match({TokenType::TRUE, TokenType::FALSE, TokenType::NIL, TokenType::STRING, TokenType::NUMBER})) {
		return new LiteralExpr(getPreviousToken());
	}

	if (match({TokenType::LEFT_PAREN})) {
		Expr* expr = expression();
		consume(TokenType::RIGHT_PAREN, "missing )");
		return new GroupingExpr(*expr);
	}

	throw error(getCurrentToken(), "Expression expected.");
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

Token Parser::advance() {
	currentTokenIndex++;
	return getPreviousToken();
}

Token Parser::consume(TokenType type, std::string msg) {
	if (checkIfCurrentTokenIs(type)) return advance();

	throw error(getCurrentToken(), msg);
}

ParseError Parser::error(Token token, std::string msg) {
	logger.error(token, msg);
	return ParseError();
}

Expr* Parser::parse() {
	try {
		return expression();
	} catch (const ParseError& err) {
		logger.error(1, "Invalid expression");
		return nullptr;
	}
}

#include "Parser.h"

#include "src/syntax/BinaryExpr.h"
#include "src/syntax/UnaryExpr.h"
#include "src/syntax/GroupingExpr.h"
#include "src/syntax/LiteralExpr.h"

#include "src/logging/LangErrorLogger.h"

Parser::Parser(std::vector<Token>& tokens, LangErrorLogger& logger):
	tokens(tokens), currentTokenIndex(0), logger(logger) {}

Expr* Parser::expression() {
	Expr* left = equality();

	while (match({TokenType::COMMA})) {
		left = equality();
	}

	return left;
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
	if (match({TokenType::BANG})) {
		Token op = getPreviousToken();
		Expr* right = unary();
		return new UnaryExpr(op, *right);
	}

	return primary();
}

Expr* Parser::primary() {
	std::initializer_list<TokenType> primaryTokenTypes = { TokenType::TRUE, TokenType::FALSE, TokenType::NIL, TokenType::STRING, TokenType::NUMBER, TokenType::IDENTIFIER };

	if (match(primaryTokenTypes)) {
		if (match(primaryTokenTypes)) {
			throw error(getCurrentToken(), "Found a primary expression after a primary expression.");
		}

		return new LiteralExpr(getPreviousToken());
	}

	if (match({TokenType::LEFT_PAREN})) {
		Expr* expr = expression();
		consume(TokenType::RIGHT_PAREN, "missing )");
		return new GroupingExpr(*expr);
	}

	// Another primary expression? That does not make sense...
	// TODO: Fix this check, it does not work. We have to peek forward and see whether we have another primary.
	// The method will be similar to 'match' but 
	

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

bool Parser::match(std::initializer_list<TokenType>&& types) {
	for (TokenType t : types) {
		if (checkIfCurrentTokenIs(t)) {
			advance();
			return true;
		}
	}

	return false;
}

bool Parser::match(std::initializer_list<TokenType>& types)
{
	return match(std::move(types));
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
		logger.error(tokens[currentTokenIndex].line, "Invalid expression");
		return nullptr;
	}
}

#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include <cstdint>
#include <initializer_list>
#include <vector>
#include <memory>

#include "src/scanner/Token.h"
#include "src/scanner/TokenType.h"
#include "src/parser/ParseError.h"
#include "src/syntax/Expr.h"
#include "src/syntax/Statement.h"

class LangErrorLogger;

/// <summary>
/// Processes the collection of tokens and builds an AST for each statement.
/// </summary>
class Parser {
public:
	Parser(std::vector<Token>&, LangErrorLogger&);

	/// <summary>
	/// Parses the tokens and returns an AST for each statement in the source code.
	/// </summary>
	/// <returns>Vector of statement ASTs</returns>
	std::vector<std::shared_ptr<Statement>> parse();
private:
	std::vector<Token>& tokens;
	int32_t currentTokenIndex;
	LangErrorLogger& logger;

	std::vector<std::shared_ptr<Statement>> program();
	std::shared_ptr<Statement> block();
	std::shared_ptr<Statement> declaration();
	std::shared_ptr<Statement> varDeclaration();
	std::shared_ptr<Statement> statement();
	std::shared_ptr<Statement> printStatement();

	std::shared_ptr<Expr> expression();
	std::shared_ptr<Expr> assignment();
	std::shared_ptr<Expr> equality();
	std::shared_ptr<Expr> comparison();
	std::shared_ptr<Expr> term();
	std::shared_ptr<Expr> factor();
	std::shared_ptr<Expr> unary();
	std::shared_ptr<Expr> primary();

	Token getPreviousToken() const;
	Token getCurrentToken() const;
	bool hasReachedEnd() const;
	Token advance();
	void undo();
	bool checkIfCurrentTokenIs(TokenType) const;
	bool match(std::initializer_list<TokenType>&&);
	bool match(std::initializer_list<TokenType>&);
	Token consume(TokenType type, std::string msg);

	ParseError error(Token token, std::string msg);

	/// <summary>
	/// When an error occurs we want to move to the next statement. This method moves the token cursor to the next statement.
	/// </summary>
	void synchronize();
};

#endif /* SRC_PARSER_PARSER_H_ */

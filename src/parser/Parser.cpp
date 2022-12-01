#include "Parser.h"

#include "src/syntax/BinaryExpr.h"
#include "src/syntax/UnaryExpr.h"
#include "src/syntax/GroupingExpr.h"
#include "src/syntax/LiteralExpr.h"
#include "src/syntax/AssignmentExpr.h"

#include "src/syntax/PrintStatement.h"
#include "src/syntax/ExprStatement.h"
#include "src/syntax/VarStatement.h"

#include "src/logging/LangErrorLogger.h"

Parser::Parser(std::vector<Token>& tokens, LangErrorLogger& logger):
  tokens(tokens), currentTokenIndex(0), logger(logger) {}

std::vector<std::shared_ptr<Statement>> Parser::program()
{
  std::vector<std::shared_ptr<Statement>> statements;

  while (!hasReachedEnd()) {
    statements.push_back(declaration());
  }

  return statements;
}

std::shared_ptr<Statement> Parser::declaration()
{
  if (match({ TokenType::VAR })) {
    return varDeclaration();
  }

  return statement();
}

std::shared_ptr<Statement> Parser::varDeclaration()
{
  Token name = consume(TokenType::IDENTIFIER, "Variable name expected.");

  if (match({ TokenType::EQUAL })) {
    auto expr = expression();

    return std::make_shared<VarStatement>(name, expr);
  }

  return std::make_shared<VarStatement>(name, std::make_shared<LiteralExpr>(Token::NULL_TOKEN));
}

std::shared_ptr<Statement> Parser::statement()
{
  if (match({ TokenType::PRINT })) {
    return printStatement();
  }

  auto expr = expression();

  //consume(TokenType::SEMICOLON, "; expected at the end of statement.");

  return std::make_shared<ExprStatement>(expr);
}

std::shared_ptr<Statement> Parser::printStatement()
{
  auto right = expression();

  //consume(TokenType::SEMICOLON, "; expected at the end of statement.");

  return std::make_shared<PrintStatement>(right);
}

std::shared_ptr<Expr> Parser::expression() {
  auto left = assignment();

  while (match({TokenType::COMMA})) {
    left = assignment();
  }

  return left;
}

std::shared_ptr<Expr> Parser::assignment()
{
  if (match({ TokenType::IDENTIFIER })) {
    Token token = getPreviousToken();

    if (match({ TokenType::EQUAL })) {
      auto expr = assignment();

      return std::make_shared<AssignmentExpr>(token, expr);
    }
    else {
      undo();
    }
  }

  return equality();
}

std::shared_ptr<Expr> Parser::equality() {
  auto left = comparison();

  while (match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL})) {
    Token op = getPreviousToken();
    auto right = comparison();
    left = std::make_shared<BinaryExpr>(left, op, right);
  }

  return left;
}

std::shared_ptr<Expr> Parser::comparison() {
  auto left = term();

  while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
    Token op = getPreviousToken();
    auto right = term();
    left = std::make_shared<BinaryExpr>(left, op, right);
  }

  return left;
}

std::shared_ptr<Expr> Parser::term() {
  auto left = factor();

  while (match({TokenType::PLUS, TokenType::MINUS})) {
    Token op = getPreviousToken();
    auto right = factor();
    left = std::make_shared<BinaryExpr>(left, op, right);
  }

  return left;
}

std::shared_ptr<Expr> Parser::factor() {
  auto left = unary();

  while (match({TokenType::STAR, TokenType::SLASH})) {
    Token op = getPreviousToken();
    auto right = unary();
    left = std::make_shared<BinaryExpr>(left, op, right);
  }

  return left;
}

std::shared_ptr<Expr> Parser::unary() {
  if (match({TokenType::BANG, TokenType::MINUS, TokenType::PLUS})) {
    Token op = getPreviousToken();
    auto right = unary();
    return std::make_shared<UnaryExpr>(op, right);
  }

  return primary();
}

std::shared_ptr<Expr> Parser::primary() {
  std::initializer_list<TokenType> primaryTokenTypes = { TokenType::TRUE, TokenType::FALSE, TokenType::NIL, TokenType::STRING, TokenType::NUMBER, TokenType::IDENTIFIER };

  if (match(primaryTokenTypes)) {
    if (match(primaryTokenTypes)) {
      throw error(getCurrentToken(), "Found a primary expression after a primary expression.");
    }

    return std::make_shared<LiteralExpr>(getPreviousToken());
  }

  if (match({TokenType::LEFT_PAREN})) {
    auto expr = expression();
    consume(TokenType::RIGHT_PAREN, "missing )");
    return std::make_shared<GroupingExpr>(expr);
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
  return currentTokenIndex >= tokens.size() || tokens[currentTokenIndex].type == TokenType::EOFILE;
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

void Parser::undo()
{
  currentTokenIndex--;
}

Token Parser::consume(TokenType type, std::string msg) {
  if (checkIfCurrentTokenIs(type)) return advance();

  throw error(getCurrentToken(), msg);
}

ParseError Parser::error(Token token, std::string msg) {
  logger.error(token, msg);
  return ParseError();
}

void Parser::synchronize()
{
  advance();

  while (!hasReachedEnd()) {
    if (getPreviousToken().type == TokenType::SEMICOLON) { return; }

    switch (getCurrentToken().type) {
      case TokenType::CLASS:
      case TokenType::FUN:
      case TokenType::VAR:
      case TokenType::FOR:
      case TokenType::IF:
      case TokenType::WHILE:
      case TokenType::PRINT:
      case TokenType::RETURN:
        return;
    }

    advance();
  }
}

std::vector<std::shared_ptr<Statement>> Parser::parse() {
  try {
    return program();
  } catch (const ParseError& err) {
    logger.error(tokens[currentTokenIndex].line, err.what());
    return {};
  }
}

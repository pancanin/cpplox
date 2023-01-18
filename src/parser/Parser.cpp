#include "Parser.h"

#include "src/syntax/BinaryExpr.h"
#include "src/syntax/UnaryExpr.h"
#include "src/syntax/GroupingExpr.h"
#include "src/syntax/LiteralExpr.h"
#include "src/syntax/LogicalExpr.h"
#include "src/syntax/AssignmentExpr.h"
#include "src/syntax/CallExpr.h"

#include "src/syntax/PrintStatement.h"
#include "src/syntax/ExprStatement.h"
#include "src/syntax/VarStatement.h"
#include "src/syntax/BlockStatement.h"
#include "src/syntax/IfElseStatement.h"
#include "src/syntax/WhileStatement.h"
#include "src/syntax/FuncStatement.h"

#include "src/logging/LangErrorLogger.h"

Parser::Parser(std::vector<Token>& tokens, LangErrorLogger& logger, bool isReplMode):
  tokens(tokens), currentTokenIndex(0), logger(logger), isReplMode(isReplMode) {}

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
  else if (match({ TokenType::FUN })) {
    return funcDeclaration();
  }

  return statement();
}

std::shared_ptr<Statement> Parser::funcDeclaration()
{
  Token funcName = consume(TokenType::IDENTIFIER, "Function name expected");

  std::vector<Token> argumentNames = arguments();

  consume(TokenType::LEFT_BRACE, "Expected beginning of function body {");

  std::shared_ptr<Statement> body = block();

  return std::make_shared<FuncStatement>(funcName, argumentNames, body);
}

std::vector<Token> Parser::arguments()
{
  consume(TokenType::LEFT_PAREN, "Expected ( at the start of a function argument list");

  std::vector<Token> arguments;

  if (!checkIfCurrentTokenIs(TokenType::RIGHT_PAREN)) {
    do {
      arguments.push_back(consume(TokenType::IDENTIFIER, "Argument expected after comma."));
    } while (match({ TokenType::COMMA }));
  }

  consume(TokenType::RIGHT_PAREN, "Expected ) at the end of a function argument list");

  return arguments;
}

std::shared_ptr<Statement> Parser::varDeclaration()
{
  Token name = consume(TokenType::IDENTIFIER, "Variable name expected.");

  if (match({ TokenType::EQUAL })) {
    auto expr = expression();

    checkForSemicolon();

    return std::make_shared<VarStatement>(name, expr);
  }

  checkForSemicolon();

  return std::make_shared<VarStatement>(name, std::make_shared<LiteralExpr>(Token::NULL_TOKEN));
}

std::shared_ptr<Statement> Parser::statement()
{
  if (match({ TokenType::PRINT })) {
    return printStatement();
  }
  else if (match({ TokenType::LEFT_BRACE })) {
    return block();
  }
  else if (match({ TokenType::IF })) {
    return ifStatement();
  }
  else if (match({ TokenType::WHILE })) {
    return whileStatement();
  }
  else if (match({ TokenType::FOR })) {
    return forStatement();
  }

  auto expr = expression();
  return std::make_shared<ExprStatement>(expr);
}

std::shared_ptr<Statement> Parser::printStatement()
{
  auto right = expression();

  checkForSemicolon();

  return std::make_shared<PrintStatement>(right);
}

std::shared_ptr<Statement> Parser::whileStatement()
{
  consume(TokenType::LEFT_PAREN, "( expected after loop keyword.");

  auto expr = expression();

  consume(TokenType::RIGHT_PAREN, ") expected after loop expression.");

  consume(TokenType::LEFT_BRACE, "Expected an opening curly brace before loop body.");

  auto body = block();

  return std::make_shared<WhileStatement>(expr, body);
}

std::shared_ptr<Statement> Parser::forStatement()
{
  consume(TokenType::LEFT_PAREN, "( expected after 'for' keyword.");

  std::shared_ptr<Statement> initializer;

  if (match({ TokenType::VAR })) {
    initializer = varDeclaration();
  }
  else if (match({ TokenType::SEMICOLON })) {
    initializer = nullptr;
  }
  else {
    initializer = std::make_shared<ExprStatement>(expression());
  }

  std::shared_ptr<Expr> condition;

  if (getPreviousToken().type == TokenType::SEMICOLON) {
    condition = expression();
  }
  else {
    consume(TokenType::SEMICOLON, "; expected at the end of 'for' initializer.");
    condition = expression();
  }

  consume(TokenType::SEMICOLON, "; expected at the end of 'for' condition.");

  std::shared_ptr<Statement> increment = std::make_shared<ExprStatement>(expression());

  consume(TokenType::RIGHT_PAREN, ") expected.");

  auto body = statement();
  std::vector<std::shared_ptr<Statement>> bodyStatements = { body, increment };
  auto bodyAndIncrementBlock = std::make_shared<BlockStatement>(bodyStatements);
  auto forLoop = std::make_shared<WhileStatement>(condition, bodyAndIncrementBlock);
  std::vector<std::shared_ptr<Statement>> statements = { initializer, forLoop };

  return std::make_shared<BlockStatement>(statements);
}

std::shared_ptr<Statement> Parser::ifStatement()
{
  consume(TokenType::LEFT_PAREN, "( expected after 'if' keyword.");

  auto expr = expression();

  consume(TokenType::RIGHT_PAREN, ") expected after 'if' expression.");

  auto stmt = statement();

  if (match({ TokenType::ELSE })) {
    auto elseStmt = statement();

    // Create and return a statement with else clause
    return std::make_shared<IfElseStatement>(expr, stmt, elseStmt);
  }

  return std::make_shared<IfElseStatement>(expr, stmt);
}

std::shared_ptr<Statement> Parser::block()
{
  std::vector<std::shared_ptr<Statement>> statements;

  while (!hasReachedEnd() && !checkIfCurrentTokenIs(TokenType::RIGHT_BRACE)) {
    statements.push_back(declaration());
  }

  consume(TokenType::RIGHT_BRACE, "Expected } at end of block.");

  return std::make_shared<BlockStatement>(statements);
}

std::shared_ptr<Expr> Parser::expression() {
  return assignment();
}

std::shared_ptr<Expr> Parser::assignment()
{
  if (match({ TokenType::IDENTIFIER })) {
    Token token = getPreviousToken();

    if (match({ TokenType::EQUAL })) {
      auto expr = assignment();

      //checkForSemicolon();

      return std::make_shared<AssignmentExpr>(token, expr);
    }
    else {
      undo();
    }
  }

  return logicalOr();
}

std::shared_ptr<Expr> Parser::logicalOr()
{
  auto left = logicalAnd();

  while (match({ TokenType::OR })) {
    auto token = getPreviousToken();
    auto right = logicalAnd();

    left = std::make_shared<LogicalExpr>(left, token, right);
  }

  return left;
}

std::shared_ptr<Expr> Parser::logicalAnd()
{
  auto left = equality();

  while (match({ TokenType::AND })) {
    auto token = getPreviousToken();
    auto right = equality();

    left = std::make_shared<LogicalExpr>(left, token, right);
  }

  return left;
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

  return call();
}

std::shared_ptr<Expr> Parser::call()
{
  auto callee = primary();

  if (match({ TokenType::LEFT_PAREN })) {
    std::vector<std::shared_ptr<Expr>> arguments;

    if (!checkIfCurrentTokenIs(TokenType::RIGHT_PAREN)) {
      do {
        arguments.push_back(expression());
      } while (match({ TokenType::COMMA }));
    }

    Token closingParen = consume(TokenType::RIGHT_PAREN, "Missing closing parenthesis on function call.");

    consume(TokenType::SEMICOLON, "Missing ;");

    return std::make_shared<CallExpr>(callee, closingParen, arguments);
  }
  
  return callee;
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

  if (getCurrentToken().type != TokenType::SEMICOLON) {
    error(getCurrentToken(), "Expression expected.");
  }
}

Token Parser::getPreviousToken() const {
  return tokens[currentTokenIndex - 1];
}

Token Parser::getCurrentToken() const {
  return tokens[currentTokenIndex];
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

void Parser::checkForSemicolon()
{
  if (!isReplMode) {
    consume(TokenType::SEMICOLON, "Expected ;");
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

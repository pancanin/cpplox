#include "Interpreter.h"

#include "src/syntax/BinaryExpr.h"
#include "src/syntax/LiteralExpr.h"
#include "src/syntax/UnaryExpr.h"
#include "src/syntax/GroupingExpr.h"
#include "src/syntax/Expr.h"

#include "src/interpreter/RuntimeError.h"
#include "src/logging/LangErrorLogger.h"
#include "src/logging/Logger.h"

Interpreter::Interpreter(Logger& logger, LangErrorLogger& errorLogger): logger(logger), errorLogger(errorLogger) {}

LoxValue Interpreter::visitLiteralExpr(LiteralExpr& expr) {
  Token token = expr.value;

  switch (token.type) {
  case TokenType::NUMBER:
    return LoxValue(LoxType::NUMBER, token.literal);
  case TokenType::STRING:
    return LoxValue(LoxType::STRING, token.literal);
  case TokenType::TRUE:
  case TokenType::FALSE:
    return LoxValue(LoxType::BOOLEAN, token.literal);
  case TokenType::NIL:
    return LoxValue(LoxType::NIL, token.literal);
  default:
    return LoxValue(LoxType::ANY, token.literal);
  }
}

LoxValue Interpreter::visitGroupingExpr(GroupingExpr& expr) {
  return evaluate(expr.expr);
}

void Interpreter::visitPrintStatement(PrintStatement* printStatement)
{
  LoxValue value = evaluate(printStatement->_expr);

  std::cout << value.value << std::endl;
}

void Interpreter::visitExprStatement(ExprStatement* exprStatement)
{
  evaluate(exprStatement->_expr);
}

LoxValue Interpreter::visitUnaryExpr(UnaryExpr& expr) {
  LoxValue right = evaluate(expr.expr);

  if (expr.op.type == TokenType::MINUS && right.type == LoxType::NUMBER) {
    double value = std::stod(right.value);

    return LoxValue(LoxType::NUMBER, std::to_string(-value));
  } else if (expr.op.type == TokenType::BANG && right.type == LoxType::BOOLEAN) {
    return LoxValue("true" != right.value);
  }

  throw RuntimeError(expr.op, "Invalid unary expression.");
}

LoxValue Interpreter::visitBinaryExpr(BinaryExpr& expr) {
  LoxValue left = evaluate(expr.left);
  LoxValue right = evaluate(expr.right);

  if (expr.operand.type == TokenType::PLUS && (left.type == LoxType::STRING || right.type == LoxType::STRING)) {
    return LoxValue(LoxType::STRING, left.value + right.value);
  }

  if (expr.operand.type == TokenType::EQUAL_EQUAL) {
    checkSameType(expr.operand, left.type, right.type);

    return LoxValue(left.value == right.value);
  }

  if (expr.operand.type == TokenType::BANG_EQUAL) {
    checkSameType(expr.operand, left.type, right.type);
    return LoxValue(left.value != right.value);
  }

  if (expr.operand.type == TokenType::GREATER) {
    checkSameType(expr.operand, left.type, right.type);

    if (left.type == LoxType::NUMBER && right.type == LoxType::NUMBER) {
      return LoxValue(std::stod(left.value) > std::stod(right.value));
    }

    return LoxValue(left.value > right.value);
  } else if (expr.operand.type == TokenType::GREATER_EQUAL) {
    checkSameType(expr.operand, left.type, right.type);

    if (left.type == LoxType::NUMBER && right.type == LoxType::NUMBER) {
      return LoxValue(std::stod(left.value) >= std::stod(right.value));
    }

    return LoxValue(left.value >= right.value);
  } else if (expr.operand.type == TokenType::LESS) {
    checkSameType(expr.operand, left.type, right.type);

    if (left.type == LoxType::NUMBER && right.type == LoxType::NUMBER) {
      return LoxValue(std::stod(left.value) < std::stod(right.value));
    }

    return LoxValue(left.value < right.value);
  } else if (expr.operand.type == TokenType::LESS_EQUAL) {
    checkSameType(expr.operand, left.type, right.type);

    if (left.type == LoxType::NUMBER && right.type == LoxType::NUMBER) {
      return LoxValue(std::stod(left.value) <= std::stod(right.value));
    }

    return LoxValue(left.value <= right.value);
  }

  checkNumberOperand(expr.operand, left.type);
  checkNumberOperand(expr.operand, right.type);
  double leftVal = std::stod(left.value);
  double rightVal = std::stod(right.value);

  switch(expr.operand.type) {
  case TokenType::PLUS:
    return LoxValue(LoxType::NUMBER, std::to_string(leftVal + rightVal));
  case TokenType::MINUS:
    return LoxValue(LoxType::NUMBER, std::to_string(leftVal - rightVal));
  case TokenType::SLASH:
    if (rightVal == 0) { throw RuntimeError(expr.operand, "Division by zero."); } // TODO: This comparison is fishy. Let's improve it once we include BigDecimal class
    return LoxValue(LoxType::NUMBER, std::to_string(leftVal / rightVal));
  case TokenType::STAR:
    return LoxValue(LoxType::NUMBER, std::to_string(leftVal * rightVal));
  }

  return LoxValue(LoxType::NIL, "");
}

LoxValue Interpreter::evaluate(Expr& expr) {
  return expr.accept(*this);
}

void Interpreter::execute(std::shared_ptr<Statement> statement)
{
  statement->accept(*this);
}

void Interpreter::checkNumberOperand(Token op, LoxType operandType) {
  if (operandType == LoxType::NUMBER) return;
  throw RuntimeError(op, "Operands must be a number.");
}

void Interpreter::checkStringOperand(Token op, LoxType operandType) {
  if (operandType == LoxType::STRING) return;
  throw RuntimeError(op, "Operand allows for string type only.");
}

void Interpreter::checkSameType(Token op, LoxType o1Type, LoxType o2Type) {
  if (o1Type == o2Type) return;
  throw RuntimeError(op, "Operands must be of same type.");
}

void Interpreter::interpret(const std::vector<std::shared_ptr<Statement>>& statements) {
  try {
    for (auto statement : statements) {
      execute(statement);
    }

  } catch (const RuntimeError& err) {
    errorLogger.error(err.token, err.what());
  }
}

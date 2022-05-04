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

LoxValue Interpreter::visitUnaryExpr(UnaryExpr& expr) {
  LoxValue right = evaluate(expr.expr);

  if (expr.op.type == TokenType::MINUS && right.type == LoxType::NUMBER) {
    double value = std::stod(right.value);

    return LoxValue(LoxType::NUMBER, std::to_string(-value));
  } else if (expr.op.type == TokenType::BANG && right.type == LoxType::BOOLEAN) {
    bool isTrue = "true" == right.value;

    if (isTrue) {
      return LoxValue(LoxType::BOOLEAN, "false");
    } else {
      return LoxValue(LoxType::BOOLEAN, "true");
    }
  }

  return LoxValue(LoxType::NIL, "");
}

LoxValue Interpreter::visitBinaryExpr(BinaryExpr& expr) {
  LoxValue left = evaluate(expr.left);
  LoxValue right = evaluate(expr.right);

  if (expr.operand.type == TokenType::PLUS && (left.type == LoxType::STRING || right.type == LoxType::STRING)) {
    return LoxValue(LoxType::STRING, left.value + right.value);
  }

  if (expr.operand.type == TokenType::EQUAL_EQUAL) {
    checkSameType(expr.operand, left.type, right.type);
    return LoxValue(LoxType::BOOLEAN, left.value == right.value ? "true" : "false");
  }

  if (expr.operand.type == TokenType::BANG_EQUAL) {
    checkSameType(expr.operand, left.type, right.type);
    return LoxValue(LoxType::BOOLEAN, left.value != right.value ? "true" : "false");
  }

  if (expr.operand.type == TokenType::GREATER) {
    checkSameType(expr.operand, left.type, right.type);

    if (left.type == LoxType::NUMBER && right.type == LoxType::NUMBER) {
      return LoxValue(LoxType::BOOLEAN, std::stod(left.value) > std::stod(right.value) ? "true" : "false");
    }

    return LoxValue(LoxType::BOOLEAN, left.value > right.value ? "true" : "false");
  } else if (expr.operand.type == TokenType::GREATER_EQUAL) {
    checkSameType(expr.operand, left.type, right.type);

    if (left.type == LoxType::NUMBER && right.type == LoxType::NUMBER) {
      return LoxValue(LoxType::BOOLEAN, std::stod(left.value) >= std::stod(right.value) ? "true" : "false");
    }

    return LoxValue(LoxType::BOOLEAN, left.value >= right.value ? "true" : "false");
  } else if (expr.operand.type == TokenType::LESS) {
    checkSameType(expr.operand, left.type, right.type);

    if (left.type == LoxType::NUMBER && right.type == LoxType::NUMBER) {
      return LoxValue(LoxType::BOOLEAN, std::stod(left.value) < std::stod(right.value) ? "true" : "false");
    }

    return LoxValue(LoxType::BOOLEAN, left.value < right.value ? "true" : "false");
  } else if (expr.operand.type == TokenType::LESS_EQUAL) {
    checkSameType(expr.operand, left.type, right.type);

    if (left.type == LoxType::NUMBER && right.type == LoxType::NUMBER) {
      return LoxValue(LoxType::BOOLEAN, std::stod(left.value) <= std::stod(right.value) ? "true" : "false");
    }

    return LoxValue(LoxType::BOOLEAN, left.value <= right.value ? "true" : "false");
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
    return LoxValue(LoxType::NUMBER, std::to_string(leftVal / rightVal));
  case TokenType::STAR:
    return LoxValue(LoxType::NUMBER, std::to_string(leftVal * rightVal));
  }

  return LoxValue(LoxType::NIL, "");
}

LoxValue Interpreter::evaluate(Expr& expr) {
  return expr.accept(*this);
}

void Interpreter::checkNumberOperand(Token op, LoxType operandType) {
  if (operandType == LoxType::NUMBER) return;
  throw RuntimeError(op, "Operand must be a number.");
}

void Interpreter::checkSameType(Token op, LoxType o1Type, LoxType o2Type) {
  if (o1Type == o2Type) return;
  throw RuntimeError(op, "Operands must be of same type.");
}

void Interpreter::interpret(Expr& expr) {
  try {
    LoxValue value = evaluate(expr);
    logger.info(value.value);
  } catch (const RuntimeError& err) {
    errorLogger.error(err.token, err.what());
  }
}

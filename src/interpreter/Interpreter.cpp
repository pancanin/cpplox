#include "Interpreter.h"

#include "src/syntax/BinaryExpr.h"
#include "src/syntax/LiteralExpr.h"
#include "src/syntax/UnaryExpr.h"
#include "src/syntax/GroupingExpr.h"
#include "src/syntax/LogicalExpr.h"
#include "src/syntax/AssignmentExpr.h"
#include "src/syntax/CallExpr.h"
#include "src/syntax/Expr.h"
#include "src/syntax/BlockStatement.h"
#include "src/syntax/IfElseStatement.h"
#include "src/syntax/FuncStatement.h"

#include "src/interpreter/RuntimeError.h"
#include "src/logging/LangErrorLogger.h"
#include "src/logging/Logger.h"

#include "src/nativefuncs/TimeFunc.h"
#include "src/nativefuncs/SlurFunc.h"

Interpreter::Interpreter(Logger& logger, LangErrorLogger& errorLogger, std::shared_ptr<Environment> env): logger(logger), errorLogger(errorLogger), env(env) {
  // Define native, global functions
  auto timeFuncPtr = std::make_shared<TimeFunc>();
  auto slurFuncPtr = std::make_shared<SlurFunc>();
  env->define("time", timeFuncPtr);
  env->define("slur", slurFuncPtr);
}

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
  case TokenType::IDENTIFIER: {
    bool isItAVariable = env->resolveVariableDeclaration(token.literal);
    bool isItAFunc = env->hasEnvGotFunction(token.literal);

    if (isItAVariable) {
      return env->evalVariable(token.literal);
    }
    else if (isItAFunc) {
      return LoxValue(LoxType::STRING, token.literal);
    }
    else if (!isItAVariable) {
      throw RuntimeError(token, "Undefined variable");
    }
    else if (!isItAFunc) {
      throw RuntimeError(token, "Undefined function");
    }
  }
  default:
    return LoxValue(LoxType::ANY, token.literal);
  }
}

LoxValue Interpreter::visitGroupingExpr(GroupingExpr& expr) {
  return evaluate(*expr.expr);
}

LoxValue Interpreter::visitLogicalExpr(LogicalExpr& expr)
{
  auto leftVal = evaluate(*expr.left);

  if (expr.operand.type == TokenType::AND) {
    if (leftVal.isTruthy()) {
      auto rightVal = evaluate(*expr.right);

      return rightVal;
    }

    return leftVal;
  }

  else if (expr.operand.type == TokenType::OR) {
    auto rightVal = evaluate(*expr.right);

    if (leftVal.isTruthy()) {
      return leftVal;
    }
    else if (rightVal.isTruthy()) {
      return rightVal;
    }
  }

  return LoxValue();
}

LoxValue Interpreter::visitAssignExpr(AssignmentExpr& expr)
{
  auto val = evaluate(*expr.expr);

  bool isDeclared = env->assignVariable(expr.identifier.literal, val);

  if (!isDeclared) {
    throw RuntimeError(expr.identifier, "Undefined variable");
  }

  return env->evalVariable(expr.identifier.literal);
}

LoxValue Interpreter::visitCallExpr(CallExpr& expr)
{
  LoxValue callee = evaluate(*expr.callee);

  if (!env->hasEnvGotFunction(callee.value)) {
    throw RuntimeError(expr.closingBrace, "Undefined function");
  }

  std::vector<LoxValue> args;

  for (auto& argExpr : expr.argumentExpressions) {
    args.push_back(evaluate(*argExpr));
  }

  auto callable = env->resolveFunction(callee.value);

  if (callable->arity() != expr.argumentExpressions.size()) {
    throw RuntimeError(expr.closingBrace, "Argument count does not match");
  }

  return callable->call(this, args);
}

void Interpreter::visitPrintStatement(PrintStatement* printStatement)
{
  LoxValue value = evaluate(*printStatement->_exprPtr);

  std::cout << value.value << std::endl;
}

void Interpreter::visitWhileStatement(WhileStatement& whileStatement)
{
  auto value = evaluate(*whileStatement._exprPtr);

  while (value.isTruthy()) {
    execute(whileStatement.body);

    value = evaluate(*whileStatement._exprPtr);
  }
}

void Interpreter::visitExprStatement(ExprStatement* exprStatement)
{
  auto val = evaluate(*exprStatement->_expr);

  logger.info(val.value, true);
}

void Interpreter::visitVarStatement(VarStatement* statement)
{
  LoxValue val;

  if (statement->_expr.get() != nullptr) {
    val = evaluate(*statement->_expr);
  }

  if (env->doesCurrentEnvDeclareVariable(statement->name.literal)) {
    throw RuntimeError(statement->name, "Variable redeclaration.");
  }

  env->declareVariable(statement->name.literal, val);
}

void Interpreter::visitBlockStatement(BlockStatement& blockStatement)
{
  env = std::make_shared<Environment>(env);

  try {
    for (auto statement : blockStatement.statements) {
      statement->accept(*this);
    }
  }
  catch (const RuntimeError& err) {
    env = env->parent;

    throw err;
  }
  
  env = env->parent;
}

void Interpreter::visitIfElseStatement(IfElseStatement& ifElseStatement)
{
  auto ifConditionValue = evaluate(*ifElseStatement.ifExpr);

  if (ifConditionValue.type != LoxType::BOOLEAN) {
    // The RuntimeError interface is not great for supporting different types of errors.
    throw RuntimeError(Token::NULL_TOKEN, "Invalid if condition - expected a boolean expression.");
  }

  if (ifConditionValue.isTruthy()) {
    execute(ifElseStatement.ifStatement);
  }
  else if (ifElseStatement.elseStatement != nullptr) {
    execute(ifElseStatement.elseStatement);
  }
}

void Interpreter::visitFuncStatement(FuncStatement& statement)
{
  // We wont check if we already have a function with this name
  env->define(statement.name.literal, );
}

LoxValue Interpreter::visitUnaryExpr(UnaryExpr& expr) {
  LoxValue right = evaluate(*expr.expr);

  if (expr.op.type == TokenType::MINUS && right.type == LoxType::NUMBER) {
    double value = std::stod(right.value);

    return LoxValue(LoxType::NUMBER, std::to_string(-value));
  } else if (expr.op.type == TokenType::BANG && right.type == LoxType::BOOLEAN) {
    return LoxValue("true" != right.value);
  }

  throw RuntimeError(expr.op, "Invalid unary expression.");
}

LoxValue Interpreter::visitBinaryExpr(BinaryExpr& expr) {
  LoxValue left = evaluate(*expr.left);
  LoxValue right = evaluate(*expr.right);

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
  // If we do not use Visitor pattern here, then we have to have 'switch' or 'if-else'
  // So we can select an appropriate method from 'Interpreter' class based on Expr.
  // Instead, we pass the visitor to the current expression and thanks to polymorphism
  // the appropriate method in the interpreter class is called.
  // For example:
  // - Current expr is of type BinaryExpr
  // - we call 'accept' method on BinaryExpr.
  // - The implementation of accept method of BinaryExpr:
  // 
  // LoxValue accept(LoxValueExprVisitor& visitor) {
  //  return visitor.visitBinaryExpr(*this);
  // }
  //
  // - Interpreter (this) inherits from LoxValueExprVisitor
  // - inside the accept method, we call visitor.visitBinaryExpr(*this);
  // - The method is defined in Interpreter class (this) 
  // - We execute visitBinaryExpr on the Interpreter with *this which is the BinaryExpr.
  // - The respective method is called in Interpreter and BinaryExpr is handled.
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

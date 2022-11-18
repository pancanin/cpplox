#ifndef SRC_INTERPRETER_INTERPRETER_H_
#define SRC_INTERPRETER_INTERPRETER_H_

#include "src/scanner/Token.h"
#include "src/interpreter/LoxValueExprVisitor.h"
#include "src/syntax/Expr.h"
#include "src/logging/Logger.h"
#include "src/logging/LangErrorLogger.h"

class Interpreter : public LoxValueExprVisitor {
public:
  Interpreter(Logger&, LangErrorLogger&);

  void interpret(Expr& expr);

  ~Interpreter() = default;

private:
  Logger& logger;
  LangErrorLogger& errorLogger;

  LoxValue evaluate(Expr& expr);

  LoxValue visitBinaryExpr(BinaryExpr&);
  LoxValue visitLiteralExpr(LiteralExpr&);
  LoxValue visitUnaryExpr(UnaryExpr&);
  LoxValue visitGroupingExpr(GroupingExpr&);

  void checkNumberOperand(Token op, LoxType operandType);
  void checkStringOperand(Token op, LoxType operandType);
  void checkSameType(Token op, LoxType o1Type, LoxType o2Type);
};

#endif /* SRC_INTERPRETER_INTERPRETER_H_ */

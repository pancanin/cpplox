#ifndef SRC_INTERPRETER_INTERPRETER_H_
#define SRC_INTERPRETER_INTERPRETER_H_

#include <vector>

#include "src/scanner/Token.h"
#include "src/interpreter/LoxValueExprVisitor.h"
#include "src/syntax/Expr.h"
#include "src/logging/Logger.h"
#include "src/logging/LangErrorLogger.h"

#include "src/syntax/LoxStatementVisitor.h"

class Statement;
class PrintStatement;

class Interpreter : public LoxValueExprVisitor, public LoxStatementVisitor {
public:
  Interpreter(Logger&, LangErrorLogger&);

  void interpret(std::vector<Statement*>);

  ~Interpreter() = default;

private:
  Logger& logger;
  LangErrorLogger& errorLogger;

  LoxValue evaluate(Expr& expr);
  void execute(Statement*);

  LoxValue visitBinaryExpr(BinaryExpr&);
  LoxValue visitLiteralExpr(LiteralExpr&);
  LoxValue visitUnaryExpr(UnaryExpr&);
  LoxValue visitGroupingExpr(GroupingExpr&);

  void visitPrintStatement(PrintStatement*);
  void visitExprStatement(ExprStatement*);

  void checkNumberOperand(Token op, LoxType operandType);
  void checkStringOperand(Token op, LoxType operandType);
  void checkSameType(Token op, LoxType o1Type, LoxType o2Type);
};

#endif /* SRC_INTERPRETER_INTERPRETER_H_ */

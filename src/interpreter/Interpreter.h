#ifndef SRC_INTERPRETER_INTERPRETER_H_
#define SRC_INTERPRETER_INTERPRETER_H_

#include <vector>
#include <memory>

#include "src/scanner/Token.h"
#include "src/interpreter/LoxValueExprVisitor.h"
#include "src/syntax/Expr.h"
#include "src/logging/Logger.h"
#include "src/logging/LangErrorLogger.h"

#include "src/syntax/LoxStatementVisitor.h"
#include "src/syntax/Statement.h"
#include "src/env/Environment.h"

class PrintStatement;
class VarStatement;

class Interpreter : public LoxValueExprVisitor, public LoxStatementVisitor {
public:
  Interpreter(Logger&, LangErrorLogger&);

  void interpret(const std::vector<std::shared_ptr<Statement>>&);

  ~Interpreter() = default;

private:
  Logger& logger;
  LangErrorLogger& errorLogger;
  Environment env;

  LoxValue evaluate(Expr& expr);
  void execute(std::shared_ptr<Statement>);

  LoxValue visitBinaryExpr(BinaryExpr&);
  LoxValue visitLiteralExpr(LiteralExpr&);
  LoxValue visitUnaryExpr(UnaryExpr&);
  LoxValue visitGroupingExpr(GroupingExpr&);

  void visitPrintStatement(PrintStatement*);
  void visitExprStatement(ExprStatement*);
  void visitVarStatement(VarStatement*);

  void checkNumberOperand(Token op, LoxType operandType);
  void checkStringOperand(Token op, LoxType operandType);
  void checkSameType(Token op, LoxType o1Type, LoxType o2Type);
};

#endif /* SRC_INTERPRETER_INTERPRETER_H_ */

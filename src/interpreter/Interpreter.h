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
class BlockStatement;
class IfElseStatement;
class WhileStatement;
class CallExpr;
class FuncStatement;

/// <summary>
/// Recursively walks and evaluates each individual AST.
/// </summary>
class Interpreter : public LoxValueExprVisitor, public LoxStatementVisitor {
public:
  Interpreter(Logger&, LangErrorLogger&, std::shared_ptr<Environment> env);

  /// <summary>
  /// Iterates through each statement AST and evaluates it.
  /// The result, for now, is always a side effect - either changing the environment or printing to the console.
  /// </summary>
  /// <param name="statements">Collection of statement ASTs</param>
  void interpret(const std::vector<std::shared_ptr<Statement>>&);

  ~Interpreter() = default;

private:
  Logger& logger;
  LangErrorLogger& errorLogger;
  std::shared_ptr<Environment> env;

  LoxValue evaluate(Expr& expr);
  void execute(std::shared_ptr<Statement>);


  LoxValue visitLiteralExpr(LiteralExpr&);
  LoxValue visitUnaryExpr(UnaryExpr&);
  LoxValue visitBinaryExpr(BinaryExpr&);
  LoxValue visitGroupingExpr(GroupingExpr&);
  LoxValue visitLogicalExpr(LogicalExpr&);
  LoxValue visitAssignExpr(AssignmentExpr&);
  LoxValue visitCallExpr(CallExpr&);

  void visitPrintStatement(PrintStatement*);
  void visitWhileStatement(WhileStatement&);
  void visitExprStatement(ExprStatement*);
  void visitVarStatement(VarStatement*);
  void visitBlockStatement(BlockStatement&);
  void visitIfElseStatement(IfElseStatement&);
  void visitFuncStatement(FuncStatement&);

  void checkNumberOperand(Token op, LoxType operandType);
  void checkStringOperand(Token op, LoxType operandType);
  void checkSameType(Token op, LoxType o1Type, LoxType o2Type);
};

#endif /* SRC_INTERPRETER_INTERPRETER_H_ */

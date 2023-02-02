#ifndef SEMANTIC_RESOLVER_H
#define SEMANTIC_RESOLVER_H

#include <vector>
#include <stack>
#include <string>
#include <unordered_map>

#include "src/interpreter/LoxValueExprVisitor.h"
#include "src/syntax/LoxStatementVisitor.h"
#include "src/interpreter/Interpreter.h"
#include "src/scanner/Token.h"

class Expr;
class FuncStatement;

class Resolver : public LoxValueExprVisitor, public LoxStatementVisitor {
public:
  Resolver(Interpreter&);

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
  void visitReturnStatement(ReturnStatement&);

  void resolve(const std::vector<std::shared_ptr<Statement>>& statements);
private:
  Interpreter& interpreterPtr;
  std::vector<std::unordered_map<std::string, bool>> scopes;

  void beginScope();
  void endScope();

  
  void resolve(std::shared_ptr<Statement>);
  void resolve(Expr* expr);
  void resolveLocal(Expr&, Token name);
  void resolveFunction(FuncStatement&);

  void define(Token&);
};

#endif // !SEMANTIC_RESOLVER_H

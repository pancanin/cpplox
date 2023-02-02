#include "Resolver.h"

#include "src/syntax/VarStatement.h"
#include "src/syntax/AssignmentExpr.h"
#include "src/syntax/FuncStatement.h"
#include "src/syntax/WhileStatement.h"
#include "src/syntax/PrintStatement.h"
#include "src/syntax/IfElseStatement.h"
#include "src/syntax/ReturnStatement.h"
#include "src/syntax/CallExpr.h"
#include "src/syntax/LogicalExpr.h"
#include "src/syntax/BinaryExpr.h"
#include "src/syntax/GroupingExpr.h"
#include "src/syntax/UnaryExpr.h"
#include "src/syntax/LiteralExpr.h"

Resolver::Resolver(Interpreter& intrpr): interpreterPtr(intrpr)
{
}

void Resolver::visitPrintStatement(PrintStatement* printStmt)
{
  resolve(printStmt->_exprPtr.get());
}

void Resolver::visitWhileStatement(WhileStatement& whileStmt)
{
  resolve(whileStmt._exprPtr.get());
  resolve(whileStmt.body);
}

void Resolver::visitExprStatement(ExprStatement* exprStmt)
{
  resolve(exprStmt->_expr.get());
}

void Resolver::visitVarStatement(VarStatement* varstmt)
{
  define(varstmt->name);
  resolve(varstmt->_expr.get());
}

void Resolver::visitBlockStatement(BlockStatement& blockStmt)
{
  beginScope();
  resolve(blockStmt.statements);
  endScope();
}

void Resolver::visitIfElseStatement(IfElseStatement& ifStmt)
{
  resolve(ifStmt.ifExpr.get());
  resolve(ifStmt.ifStatement);
  resolve(ifStmt.elseStatement);
}

void Resolver::visitFuncStatement(FuncStatement& funcStmt)
{
  define(funcStmt.name);

}

void Resolver::visitReturnStatement(ReturnStatement& retStmt)
{
  resolve(retStmt.expr.get());
}

void Resolver::beginScope()
{
  scopes.push_back({});
}

void Resolver::endScope()
{
  scopes.pop_back();
}

void Resolver::resolve(const std::vector<std::shared_ptr<Statement>>& statements)
{
  for (auto& stmtPtr : statements) {
    resolve(stmtPtr);
  }
}

void Resolver::resolve(std::shared_ptr<Statement> stmt)
{
  stmt->accept(*this);
}

void Resolver::resolve(Expr* expr)
{
  expr->accept(*this);
}

void Resolver::resolveLocal(Expr& expr, Token name)
{
  for (int32_t i = scopes.size() - 1; i >= 0; --i) {
    if (scopes[i].find(name.lexeme) != scopes[i].end()) {
      interpreterPtr.resolve(expr, scopes.size() - 1 - i);
      return;
    }
  }
}

void Resolver::resolveFunction(FuncStatement& funcStmt)
{
  beginScope();
  for (auto& param : funcStmt.argumentNames) {
    define(param);
  }
  resolve(funcStmt.funcBody);
  endScope();
}

void Resolver::define(Token& token)
{
  if (scopes.empty()) return;

  scopes[scopes.size() - 1][token.lexeme] = true;
}

LoxValue Resolver::visitLiteralExpr(LiteralExpr& litExpr)
{
  return LoxValue();
}

LoxValue Resolver::visitUnaryExpr(UnaryExpr& unExpr)
{
  resolve(unExpr.expr.get());
  return LoxValue();
}

LoxValue Resolver::visitBinaryExpr(BinaryExpr& binExpr)
{
  resolve(binExpr.left.get());
  resolve(binExpr.right.get());
  return LoxValue();
}

LoxValue Resolver::visitGroupingExpr(GroupingExpr& grpExpr)
{
  resolve(grpExpr.expr.get());
  return LoxValue();
}

LoxValue Resolver::visitLogicalExpr(LogicalExpr& logExpr)
{
  resolve(logExpr.left.get());
  resolve(logExpr.right.get());
  return LoxValue();
}

LoxValue Resolver::visitAssignExpr(AssignmentExpr& expr)
{
  resolve(expr.expr.get());
  resolveLocal(expr, expr.identifier);

  return LoxValue();
}

LoxValue Resolver::visitCallExpr(CallExpr& callExpr)
{
  resolve(callExpr.callee.get());

  for (auto& arg : callExpr.argumentExpressions) {
    resolve(arg.get());
  }

  return LoxValue();
}

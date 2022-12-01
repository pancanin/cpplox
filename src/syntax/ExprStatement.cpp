#include "ExprStatement.h"

#include "LoxStatementVisitor.h"

ExprStatement::ExprStatement(std::shared_ptr<Expr> expr) : _expr(expr) {}

void ExprStatement::accept(LoxStatementVisitor& visitor)
{
  visitor.visitExprStatement(this);
}

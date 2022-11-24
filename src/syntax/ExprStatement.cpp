#include "ExprStatement.h"

#include "LoxStatementVisitor.h"

ExprStatement::ExprStatement(Expr& expr) : _expr(expr) {}

void ExprStatement::accept(LoxStatementVisitor& visitor)
{
  visitor.visitExprStatement(this);
}

#include "IfElseStatement.h"

#include "LoxStatementVisitor.h"

IfElseStatement::IfElseStatement(std::shared_ptr<Expr> ifExpr, std::shared_ptr<Statement> ifStatement, std::shared_ptr<Statement> elseStatement):
  ifExpr(ifExpr),
  ifStatement(ifStatement),
  elseStatement(elseStatement)
{
}

IfElseStatement::IfElseStatement(std::shared_ptr<Expr> ifExpr, std::shared_ptr<Statement> ifStatement) :
  IfElseStatement(ifExpr, ifStatement, nullptr)
{
}

void IfElseStatement::accept(LoxStatementVisitor& visitor)
{
  visitor.visitIfElseStatement(*this);
}

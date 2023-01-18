#include "ReturnStatement.h"

#include "src/syntax/LoxStatementVisitor.h"

ReturnStatement::ReturnStatement(Token keyword, std::shared_ptr<Expr> expr): keyword(keyword), expr(expr)
{
}

void ReturnStatement::accept(LoxStatementVisitor& visitor)
{
  visitor.visitReturnStatement(*this);
}

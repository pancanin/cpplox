#include "CallExpr.h"

#include "../interpreter/LoxValueExprVisitor.h"

CallExpr::CallExpr(std::shared_ptr<Expr> callee, Token closingBrace, std::vector<std::shared_ptr<Expr>> arguments):
  callee(callee),
  closingBrace(closingBrace),
  argumentExpressions(arguments)
{}

LoxValue CallExpr::accept(LoxValueExprVisitor& visitor)
{
  return visitor.visitCallExpr(*this);
}

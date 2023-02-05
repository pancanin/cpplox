#include "GetExpr.h"

#include "src/interpreter/LoxValueExprVisitor.h"
#include "src/syntax/Expr.h"

GetExpr::GetExpr(std::shared_ptr<Expr> expr, Token& name): objectExpr(expr), propertyName(name)
{
}

std::string GetExpr::accept(ToStringExprVisitor&)
{
	return std::string();
}

LoxValue GetExpr::accept(LoxValueExprVisitor& visitor)
{
	return visitor.visitGetExpr(*this);
}

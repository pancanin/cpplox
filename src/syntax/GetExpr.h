#ifndef SYNTAX_GET_EXPR_H
#define SYNTAX_GET_EXPR_H

#include "Expr.h"

#include <string>
#include <memory>

#include "src/interpreter/LoxValue.h"
#include "src/scanner/Token.h"
#include "src/syntax/Expr.h"

class ToStringExprVisitor;
class LoxValueExprVisitor;

class GetExpr : public Expr {
public:
	GetExpr(std::shared_ptr<Expr>, Token&);

	std::string accept(ToStringExprVisitor&);
	LoxValue accept(LoxValueExprVisitor&);

	std::shared_ptr<Expr> objectExpr;
	Token propertyName;
};

#endif // !SYNTAX_GET_EXPR_H

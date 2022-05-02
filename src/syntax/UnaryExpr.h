#ifndef SRC_SYNTAX_UNARYEXPR_H_
#define SRC_SYNTAX_UNARYEXPR_H_

#include <string>

#include "src/scanner/Token.h"
#include "src/syntax/Expr.h"
#include "src/syntax/ToStringExprVisitor.h"

class UnaryExpr : public Expr {
public:
	UnaryExpr(Token op, Expr& expr): op(op), expr(expr) {}

	Token op;
	Expr& expr;

	std::string accept(ToStringExprVisitor& visitor) {
		return visitor.visitUnaryExpr(*this);
	}
};


#endif /* SRC_SYNTAX_UNARYEXPR_H_ */

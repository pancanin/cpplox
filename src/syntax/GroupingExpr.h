#ifndef SRC_SYNTAX_GROUPINGEXPR_H_
#define SRC_SYNTAX_GROUPINGEXPR_H_

#include "src/syntax/Expr.h"

class GroupingExpr : public Expr {
public:
	GroupingExpr(Expr& expr): expr(expr) {}

	Expr& expr;

	std::string accept(ToStringExprVisitor& visitor) {
		return visitor.visitGroupingExpr(*this);
	}
};


#endif /* SRC_SYNTAX_GROUPINGEXPR_H_ */

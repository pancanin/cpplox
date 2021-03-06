#ifndef SRC_SYNTAX_GROUPINGEXPR_H_
#define SRC_SYNTAX_GROUPINGEXPR_H_

#include "src/syntax/Expr.h"
#include "src/interpreter/LoxValue.h"
#include "src/interpreter/LoxValueExprVisitor.h"

class GroupingExpr : public Expr {
public:
	GroupingExpr(Expr& expr): expr(expr) {}

	Expr& expr;

	std::string accept(ToStringExprVisitor& visitor) {
		return visitor.visitGroupingExpr(*this);
	}

	LoxValue accept(LoxValueExprVisitor& visitor) {
    return visitor.visitGroupingExpr(*this);
  }
};


#endif /* SRC_SYNTAX_GROUPINGEXPR_H_ */

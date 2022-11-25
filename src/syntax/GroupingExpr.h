#ifndef SRC_SYNTAX_GROUPINGEXPR_H_
#define SRC_SYNTAX_GROUPINGEXPR_H_

#include <memory>

#include "src/syntax/Expr.h"
#include "src/interpreter/LoxValue.h"
#include "src/interpreter/LoxValueExprVisitor.h"

class GroupingExpr : public Expr {
public:
	GroupingExpr(std::shared_ptr<Expr> expr): expr(expr) {}

	std::shared_ptr<Expr> expr;

	std::string accept(ToStringExprVisitor& visitor) {
		return visitor.visitGroupingExpr(*this);
	}

	LoxValue accept(LoxValueExprVisitor& visitor) {
    return visitor.visitGroupingExpr(*this);
  }
};


#endif /* SRC_SYNTAX_GROUPINGEXPR_H_ */

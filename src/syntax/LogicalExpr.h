#ifndef SRC_SYNTAX_LOGICALEXPR_H_
#define SRC_SYNTAX_LOGICALEXPR_H_

#include <memory>

#include "src/syntax/Expr.h"
#include "src/scanner/Token.h"
#include "src/syntax/ToStringExprVisitor.h"
#include "src/interpreter/LoxValue.h"
#include "src/interpreter/LoxValueExprVisitor.h"

class LogicalExpr : public Expr {
public:
	LogicalExpr(std::shared_ptr<Expr> left, Token operand, std::shared_ptr<Expr> right) : left(left), operand(operand), right(right) {}

	std::shared_ptr<Expr> left;
	Token operand;
	std::shared_ptr<Expr> right;

	std::string accept(ToStringExprVisitor& visitor) {
		return {};
	}

	LoxValue accept(LoxValueExprVisitor& visitor) {
		return visitor.visitLogicalExpr(*this);
	}
};

#endif /* SRC_SYNTAX_LOGICALEXPR_H_ */

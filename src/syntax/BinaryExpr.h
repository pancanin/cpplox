#ifndef SRC_SYNTAX_BINARYEXPR_H_
#define SRC_SYNTAX_BINARYEXPR_H_

#include "src/syntax/Expr.h"
#include "src/scanner/Token.h"
#include "src/syntax/ToStringExprVisitor.h"

class BinaryExpr : public Expr {
public:
	BinaryExpr(Expr& left, Token operand, Expr& right): left(left), operand(operand), right(right) {}

	Expr& left;
	Token operand;
	Expr& right;

	std::string accept(ToStringExprVisitor& visitor) {
		return visitor.visitBinaryExpr(*this);
	}
};

#endif /* SRC_SYNTAX_BINARYEXPR_H_ */

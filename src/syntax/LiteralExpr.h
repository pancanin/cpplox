#ifndef SRC_SYNTAX_LITERALEXPR_H_
#define SRC_SYNTAX_LITERALEXPR_H_

#include "src/syntax/Expr.h"
#include "src/scanner/Token.h"

class LiteralExpr : public Expr {
public:
	LiteralExpr(Token literalToken): value(literalToken) {}

	Token value;

	std::string accept(ToStringExprVisitor& visitor) {
		return visitor.visitLiteralExpr(*this);
	}
};

#endif /* SRC_SYNTAX_LITERALEXPR_H_ */

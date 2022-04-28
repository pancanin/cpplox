#ifndef SRC_SYNTAX_EXPR_H_
#define SRC_SYNTAX_EXPR_H_

#include "src/scanner/Token.h"

#include "src/syntax/ExprVisitor.h"

class Expr {
public:
	template <typename R>
	virtual void accept(ExprVisitor<R>) = 0;

	class Binary : public Expr {
	public:
		Binary(Expr left, Token operand, Expr right): left(left), operand(operand), right(right) {}

		Expr left;
		Token operand;
		Expr right;

		// TODO: This can be extracted as macro.
		template <typename R>
		void accept(ExprVisitor<R> visitor) {
			visitor.visitBinaryExpr(this);
		}
	};

	virtual ~Expr();
};


#endif /* SRC_SYNTAX_EXPR_H_ */

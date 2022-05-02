#ifndef SRC_SYNTAX_EXPR_H_
#define SRC_SYNTAX_EXPR_H_

#include <string>

struct ToStringExprVisitor;

class Expr {
public:
	virtual std::string accept(ToStringExprVisitor&) = 0;

	virtual ~Expr() {};
};

#endif /* SRC_SYNTAX_EXPR_H_ */

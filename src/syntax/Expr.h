#ifndef SRC_SYNTAX_EXPR_H_
#define SRC_SYNTAX_EXPR_H_

#include <string>

#include "src/interpreter/LoxValue.h"

struct ToStringExprVisitor;
struct LoxValueExprVisitor;

class Expr {
public:
	virtual std::string accept(ToStringExprVisitor&) = 0;
	virtual LoxValue accept(LoxValueExprVisitor&) = 0;

	virtual ~Expr() {};
};

#endif /* SRC_SYNTAX_EXPR_H_ */

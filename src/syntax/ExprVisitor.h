#ifndef SRC_SYNTAX_EXPRVISITOR_H_
#define SRC_SYNTAX_EXPRVISITOR_H_

struct Expr {
	struct Binary;
};

template <typename R>
class ExprVisitor {
public:
	virtual R visitBinaryExpr(Expr::Binary&) = 0;

	virtual ~ExprVisitor();
};

#endif /* SRC_SYNTAX_EXPRVISITOR_H_ */

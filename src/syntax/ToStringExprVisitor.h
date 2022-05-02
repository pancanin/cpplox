#ifndef SRC_SYNTAX_TOSTRINGEXPRVISITOR_H_
#define SRC_SYNTAX_TOSTRINGEXPRVISITOR_H_

#include <string>

struct BinaryExpr;
struct LiteralExpr;
struct UnaryExpr;

class ToStringExprVisitor {
public:
	virtual std::string visitBinaryExpr(BinaryExpr&) = 0;
	virtual std::string visitLiteralExpr(LiteralExpr&) = 0;
	virtual std::string visitUnaryExpr(UnaryExpr&) = 0;

	virtual ~ToStringExprVisitor() {};
};

#endif /* SRC_SYNTAX_TOSTRINGEXPRVISITOR_H_ */

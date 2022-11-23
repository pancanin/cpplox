#ifndef SRC_SYNTAX_ASTPRINTER_H_
#define SRC_SYNTAX_ASTPRINTER_H_

#include <string>
#include <initializer_list>

#include "src/syntax/ToStringExprVisitor.h"

class BinaryExpr;
class LiteralExpr;
class UnaryExpr;
class Expr;

class AstPrinter : public ToStringExprVisitor {
public:
	std::string print(Expr& expr);
private:
	std::string visitBinaryExpr(BinaryExpr&);
	std::string visitLiteralExpr(LiteralExpr&);
	std::string visitUnaryExpr(UnaryExpr&);
	std::string visitGroupingExpr(GroupingExpr&);

	std::string parentesize(std::string name, std::initializer_list<Expr*> expressions);
};

#endif /* SRC_SYNTAX_ASTPRINTER_H_ */

#ifndef SRC_SYNTAX_ASTPRINTER_H_
#define SRC_SYNTAX_ASTPRINTER_H_

#include <string>
#include <initializer_list>

#include "src/syntax/ToStringExprVisitor.h"
#include "src/syntax/Expr.h"

struct BinaryExpr;
struct LiteralExpr;
struct UnaryExpr;

class AstPrinter : public ToStringExprVisitor {
public:
	std::string print(Expr& expr);
private:
	std::string visitBinaryExpr(BinaryExpr&);
	std::string visitLiteralExpr(LiteralExpr&);
	std::string visitUnaryExpr(UnaryExpr&);

	std::string parentesize(std::string& name, std::initializer_list<Expr*> expressions);
};

#endif /* SRC_SYNTAX_ASTPRINTER_H_ */

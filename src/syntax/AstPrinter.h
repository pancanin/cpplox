#ifndef SRC_SYNTAX_ASTPRINTER_H_
#define SRC_SYNTAX_ASTPRINTER_H_

#include <string>
#include <initializer_list>

#include "src/syntax/ExprVisitor.h"

class AstPrinter : public ExprVisitor<std::string> {
public:
	std::string print(Expr expr);
	std::string visitBinaryExpr(Expr::Binary&);
private:
	std::string parentesize(std::string& name, std::initializer_list<Expr> expressions);
};

#endif /* SRC_SYNTAX_ASTPRINTER_H_ */

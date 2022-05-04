#ifndef SRC_SYNTAX_TOSTRINGEXPRVISITOR_H_
#define SRC_SYNTAX_TOSTRINGEXPRVISITOR_H_

#include <string>

#include "src/syntax/ExprVisitor.h"

class ToStringExprVisitor : public ExprVisitor<std::string> {
public:
	virtual ~ToStringExprVisitor() {};
};

#endif /* SRC_SYNTAX_TOSTRINGEXPRVISITOR_H_ */

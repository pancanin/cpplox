#ifndef SRC_INTERPRETER_LOXVALUEEXPRVISITOR_H_
#define SRC_INTERPRETER_LOXVALUEEXPRVISITOR_H_

#include "src/syntax/ExprVisitor.h"
#include "src/interpreter/LoxValue.h"

class LoxValueExprVisitor : public ExprVisitor<LoxValue> {};

#endif /* SRC_INTERPRETER_LOXVALUEEXPRVISITOR_H_ */

#ifndef SRC_SYNTAX_STATEMENT_VISITOR_H
#define SRC_SYNTAX_STATEMENT_VISITOR_H

#include "src/syntax/PrintStatement.h"
#include "src/syntax/ExprStatement.h"
#include "src/syntax/VarStatement.h"

template <typename R>
class StatementVisitor {
public:

  // TODO: These here are raw pointers -> change them to smart pointers or references
  virtual R visitPrintStatement(PrintStatement*) = 0;
  virtual R visitExprStatement(ExprStatement*) = 0;
  virtual R visitVarStatement(VarStatement*) = 0;
  virtual R visitBlockStatement(BlockStatement&) = 0;

  virtual ~StatementVisitor() = default;
};

#endif // !SRC_SYNTAX_STATEMENT_VISITOR_H

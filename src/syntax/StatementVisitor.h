#ifndef SRC_SYNTAX_STATEMENT_VISITOR_H
#define SRC_SYNTAX_STATEMENT_VISITOR_H

#include "src/syntax/PrintStatement.h"
#include "src/syntax/ExprStatement.h"

template <typename R>
class StatementVisitor {
public:
  virtual R visitPrintStatement(PrintStatement*) = 0;
  virtual R visitExprStatement(ExprStatement*) = 0;

  virtual ~StatementVisitor() = default;
};

#endif // !SRC_SYNTAX_STATEMENT_VISITOR_H
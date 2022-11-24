#ifndef SRC_SYNTAX_EXPR_STATEMENT_H
#define SRC_SYNTAX_EXPR_STATEMENT_H

#include "Statement.h"

#include "Expr.h"

class LoxStatementVisitor;

class ExprStatement : public Statement {
public:
  ExprStatement(Expr& expr);

  void accept(LoxStatementVisitor&);

  Expr& _expr;
};

#endif // !SRC_SYNTAX_EXPR_STATEMENT_H

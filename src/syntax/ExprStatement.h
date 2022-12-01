#ifndef SRC_SYNTAX_EXPR_STATEMENT_H
#define SRC_SYNTAX_EXPR_STATEMENT_H

#include <memory>

#include "Statement.h"

#include "Expr.h"

class LoxStatementVisitor;

class ExprStatement : public Statement {
public:
  ExprStatement(std::shared_ptr<Expr> expr);

  void accept(LoxStatementVisitor&);

  std::shared_ptr<Expr> _expr;
};

#endif // !SRC_SYNTAX_EXPR_STATEMENT_H

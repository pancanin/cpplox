#ifndef SRC_SYNTAX_PRINT_STATEMENT_H
#define SRC_SYNTAX_PRINT_STATEMENT_H

#include "Statement.h"
#include "Expr.h"

#include "src/syntax/LoxStatementVisitor.h"

class PrintStatement : public Statement {
public:
  PrintStatement(Expr& expr) : _expr(expr) {};

  void accept(LoxStatementVisitor& visitor) {
    visitor.visitPrintStatement(this);
  }

  Expr& _expr;
};

#endif // !SRC_SYNTAX_PRINT_STATEMENT_H

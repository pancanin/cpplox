#ifndef SRC_SYNTAX_PRINT_STATEMENT_H
#define SRC_SYNTAX_PRINT_STATEMENT_H

#include "src/syntax/Statement.h"
#include "src/syntax/Expr.h"

class LoxStatementVisitor;

class PrintStatement : public Statement {
public:
  PrintStatement(Expr& expr);

  void accept(LoxStatementVisitor& visitor);

  Expr& _expr;
};

#endif // !SRC_SYNTAX_PRINT_STATEMENT_H

#ifndef SRC_SYNTAX_PRINT_STATEMENT_H
#define SRC_SYNTAX_PRINT_STATEMENT_H

#include <memory>

#include "src/syntax/Statement.h"
#include "src/syntax/Expr.h"

class LoxStatementVisitor;

class PrintStatement : public Statement {
public:
  PrintStatement(std::shared_ptr<Expr> exprPtr);

  void accept(LoxStatementVisitor& visitor);

  std::shared_ptr<Expr> _exprPtr;
};

#endif // !SRC_SYNTAX_PRINT_STATEMENT_H

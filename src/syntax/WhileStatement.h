#ifndef SRC_SYNTAX_WHILE_STATEMENT_H
#define SRC_SYNTAX_WHILE_STATEMENT_H

#include <memory>

#include "src/syntax/Statement.h"
#include "src/syntax/Expr.h"

class LoxStatementVisitor;

class WhileStatement : public Statement {
public:
  WhileStatement(std::shared_ptr<Expr> conditionalExpr, std::shared_ptr<Statement> body);

  void accept(LoxStatementVisitor& visitor);

  std::shared_ptr<Expr> _exprPtr;
  std::shared_ptr<Statement> body;
};

#endif // !SRC_SYNTAX_WHILE_STATEMENT_H

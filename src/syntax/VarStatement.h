#ifndef SRC_SYNTAX_VAR_STATEMENT_H
#define SRC_SYNTAX_VAR_STATEMENT_H

#include <memory>

#include "Statement.h"
#include "Expr.h"
#include "src/scanner/Token.h"

class LoxStatementVisitor;

class VarStatement : public Statement {
public:
  VarStatement(const Token& name, std::shared_ptr<Expr> expr);
  VarStatement(const Token& name);

  void accept(LoxStatementVisitor&);

  Token name;
  std::shared_ptr<Expr> _expr;
};

#endif // !SRC_SYNTAX_VAR_STATEMENT_H

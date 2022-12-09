#ifndef SRC_SYNTAX_IF_ELSE_STATEMENT_H
#define SRC_SYNTAX_IF_ELSE_STATEMENT_H

#include <memory>

#include "Statement.h"
#include "Expr.h"

class LoxStatementVisitor;

class IfElseStatement : public Statement {
public:
  IfElseStatement(std::shared_ptr<Expr> ifExpr, std::shared_ptr<Statement> ifStatement);
  IfElseStatement(std::shared_ptr<Expr> ifExpr, std::shared_ptr<Statement> ifStatement, std::shared_ptr<Statement> elseStatement);

  void accept(LoxStatementVisitor&);

  std::shared_ptr<Expr> ifExpr;
  std::shared_ptr<Statement> ifStatement;
  std::shared_ptr<Statement> elseStatement;
};

#endif // !SRC_SYNTAX_IF_ELSE_STATEMENT_H

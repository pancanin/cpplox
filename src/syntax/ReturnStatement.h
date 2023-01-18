#ifndef SYNTAX_RETURN_STMT_H
#define SYNTAX_RETURN_STMT_H

#include <memory>

#include "src/syntax/Statement.h"
#include "src/syntax/Expr.h"
#include "src/scanner/Token.h"

class ReturnStatement : public Statement {
public:
  ReturnStatement(Token keyword, std::shared_ptr<Expr> expr);

  void accept(LoxStatementVisitor&);

  Token keyword;
  std::shared_ptr<Expr> expr;
};

#endif // !SYNTAX_RETURN_STMT_H

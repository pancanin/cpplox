#ifndef SYNTAX_CALL_EXPR_H
#define SYNTAX_CALL_EXPR_H

#include <vector>
#include <memory>

#include "Expr.h"
#include "../scanner/Token.h"

class LoxValueExprVisitor;
class ToStringExprVisitor;

class CallExpr : public Expr {
public:
  CallExpr(std::shared_ptr<Expr>, Token, std::vector<std::shared_ptr<Expr>>);

  std::shared_ptr<Expr> callee;
  Token closingBrace; // used to get the position of the function for error reporting
  std::vector<std::shared_ptr<Expr>> argumentExpressions;

  std::string accept(ToStringExprVisitor&) { return {}; }

  LoxValue accept(LoxValueExprVisitor&);
};

#endif // !SYNTAX_CALL_EXPR_H



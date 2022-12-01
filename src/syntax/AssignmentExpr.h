#ifndef SRC_SYNTAX_ASSIGNMENT_EXPR_H
#define SRC_SYNTAX_ASSIGNMENT_EXPR_H

#include <memory>

#include "Expr.h"
#include "src/scanner/Token.h"

#include "src/interpreter/LoxValueExprVisitor.h"
#include "ToStringExprVisitor.h"

class AssignmentExpr : public Expr {
public:
  AssignmentExpr(const Token& identifier, std::shared_ptr<Expr> expr) : identifier(identifier), expr(expr) {}

  Token identifier;
  std::shared_ptr<Expr> expr;

  std::string accept(ToStringExprVisitor& visitor) {
    return visitor.visitAssignExpr(*this);
  }

  LoxValue accept(LoxValueExprVisitor& visitor) {
    return visitor.visitAssignExpr(*this);
  }
};

#endif
#include "WhileStatement.h"

#include "LoxStatementVisitor.h"

WhileStatement::WhileStatement(std::shared_ptr<Expr> exprPtr, std::shared_ptr<Statement> body) : _exprPtr(exprPtr), body(body) {}

void WhileStatement::accept(LoxStatementVisitor& visitor) {
  visitor.visitWhileStatement(*this);
}
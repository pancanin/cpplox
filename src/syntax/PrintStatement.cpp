#include "PrintStatement.h"

#include "LoxStatementVisitor.h"

PrintStatement::PrintStatement(std::shared_ptr<Expr> exprPtr): _exprPtr(exprPtr) {}

void PrintStatement::accept(LoxStatementVisitor& visitor) {
  visitor.visitPrintStatement(this);
}
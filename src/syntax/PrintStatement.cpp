#include "PrintStatement.h"

#include "LoxStatementVisitor.h"

PrintStatement::PrintStatement(Expr& expr): _expr(expr) {}

void PrintStatement::accept(LoxStatementVisitor& visitor) {
  visitor.visitPrintStatement(this);
}
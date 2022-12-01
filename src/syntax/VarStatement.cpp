#include "VarStatement.h"

#include "LoxStatementVisitor.h"

VarStatement::VarStatement(const Token& name, std::shared_ptr<Expr> expr) : name(name), _expr(expr) {}

void VarStatement::accept(LoxStatementVisitor& visitor) {
  visitor.visitVarStatement(this);
}
#include "VarStatement.h"

#include "LoxStatementVisitor.h"

VarStatement::VarStatement(const Token& name, std::shared_ptr<Expr> expr) : name(name), _expr(expr) {}

VarStatement::VarStatement(const Token& name): name(name) {}

void VarStatement::accept(LoxStatementVisitor& visitor) {
  visitor.visitVarStatement(this);
}
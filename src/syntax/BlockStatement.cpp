#include "BlockStatement.h"

#include "LoxStatementVisitor.h"

BlockStatement::BlockStatement(std::vector<std::shared_ptr<Statement>> statements): statements(statements) {}

void BlockStatement::accept(LoxStatementVisitor& visitor)
{
  visitor.visitBlockStatement(*this);
}

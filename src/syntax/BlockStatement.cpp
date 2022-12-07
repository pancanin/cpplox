#include "BlockStatement.h"

#include "LoxStatementVisitor.h"

BlockStatement::BlockStatement(std::shared_ptr<Statement> statement): statement(statement) {}

void BlockStatement::accept(LoxStatementVisitor& visitor)
{
  visitor.visitBlockStatement(*this);
}

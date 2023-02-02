#include "ClassStatement.h"

#include "src/syntax/LoxStatementVisitor.h"

ClassStatement::ClassStatement(const Token& name, const std::vector<std::shared_ptr<Statement>>& methods):
  name(name),
  methods(methods) {}

void ClassStatement::accept(LoxStatementVisitor& visitor)
{
  visitor.visitClassStatement(*this);
}

#include "FuncStatement.h"

#include "src/syntax/LoxStatementVisitor.h"

FuncStatement::FuncStatement(Token& name, std::vector<Token>& args, std::shared_ptr<Statement> body):
  name(name),
  argumentNames(args),
  funcBody(body)
{}

void FuncStatement::accept(LoxStatementVisitor& visitor)
{
  visitor.visitFuncStatement(*this);
}

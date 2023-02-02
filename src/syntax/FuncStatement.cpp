#include "FuncStatement.h"

#include "src/syntax/LoxStatementVisitor.h"
#include "src/interpreter/Interpreter.h"

FuncStatement::FuncStatement(const std::string& type, Token& name, std::vector<Token>& args, std::shared_ptr<Statement> body):
  type(type),
  name(name),
  argumentNames(args),
  funcBody(body)
{}

void FuncStatement::accept(LoxStatementVisitor& visitor)
{
  visitor.visitFuncStatement(*this);
}

LoxValue FuncStatement::call(Interpreter* interpreter, std::vector<LoxValue> args)
{
  return interpreter->evalUserDefinedFunc(argumentNames, args, funcBody, closure);
}

uint32_t FuncStatement::arity()
{
  return argumentNames.size();
}

void FuncStatement::setClosure(std::shared_ptr<Environment> closure)
{
  this->closure = std::make_shared<Environment>(*closure);
}

#include "FuncStatement.h"

#include "src/syntax/LoxStatementVisitor.h"
#include "src/interpreter/Interpreter.h"

FuncStatement::FuncStatement(Token& name, std::vector<Token>& args, std::shared_ptr<Statement> body):
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
  return interpreter->evalUserDefinedFunc(argumentNames, args, funcBody);
}

uint32_t FuncStatement::arity()
{
  return argumentNames.size();
}

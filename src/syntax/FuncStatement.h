#ifndef SYNTAX_FUNC_STATEMENT_H
#define SYNTAX_FUNC_STATEMENT_H

#include <vector>
#include <cstdint>
#include <memory>

#include "Statement.h"
#include "src/scanner/Token.h"
#include "src/syntax/Statement.h"
#include "src/interpreter/LoxCallable.h"
#include "src/interpreter/LoxValue.h"
#include "src/env/Environment.h"

class Interpreter;

class FuncStatement : public Statement, public LoxCallable {
public:
  FuncStatement(Token& name, std::vector<Token>& args, std::shared_ptr<Statement>);
  void accept(LoxStatementVisitor&);

  LoxValue call(Interpreter*, std::vector<LoxValue> args);
  uint32_t arity();
  void setClosure(std::shared_ptr<Environment> closure);

  Token name;
  std::vector<Token> argumentNames;
  std::shared_ptr<Statement> funcBody;
  std::shared_ptr<Environment> closure;
};

#endif // !SYNTAX_FUNC_STATEMENT_H

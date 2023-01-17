#ifndef SYNTAX_FUNC_STATEMENT_H
#define SYNTAX_FUNC_STATEMENT_H

#include <vector>
#include <cstdint>

#include "Statement.h"
#include "src/scanner/Token.h"
#include "src/syntax/Statement.h"
#include "src/interpreter/LoxCallable.h"
#include "src/interpreter/LoxValue.h"

class Interpreter;

class FuncStatement : public Statement, public LoxCallable {
public:
  FuncStatement(Token& name, std::vector<Token>& args, std::shared_ptr<Statement>);
  void accept(LoxStatementVisitor&);

  LoxValue call(Interpreter*, std::vector<LoxValue> args);
  uint32_t arity();

  Token name;
  std::vector<Token> argumentNames;
  std::shared_ptr<Statement> funcBody;
};

#endif // !SYNTAX_FUNC_STATEMENT_H

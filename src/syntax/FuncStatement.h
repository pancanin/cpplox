#ifndef SYNTAX_FUNC_STATEMENT_H
#define SYNTAX_FUNC_STATEMENT_H

#include <vector>

#include "Statement.h"
#include "src/scanner/Token.h"
#include "src/syntax/Statement.h"

class FuncStatement : public Statement {
public:
  FuncStatement(Token& name, std::vector<Token>& args, std::shared_ptr<Statement>);
  void accept(LoxStatementVisitor&);

  Token name;
  std::vector<Token> argumentNames;
  std::shared_ptr<Statement> funcBody;
};

#endif // !SYNTAX_FUNC_STATEMENT_H

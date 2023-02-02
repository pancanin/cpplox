#ifndef SYNTAX_CLASS_STATEMENT_H
#define SYNTAX_CLASS_STATEMENT_H

#include <vector>

#include "Statement.h"
#include "src/scanner/Token.h"

class LoxStatementVisitor;

class ClassStatement : public Statement {
public:
  ClassStatement(const Token&, const std::vector<std::shared_ptr<Statement>>&);
  void accept(LoxStatementVisitor&);

  Token name;
  std::vector<std::shared_ptr<Statement>> methods;
};

#endif // !SYNTAX_CLASS_STATEMENT_H

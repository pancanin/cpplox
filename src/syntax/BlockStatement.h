#ifndef SRC_SYNTAX_BLOCK_STATEMENT_H
#define SRC_SYNTAX_BLOCK_STATEMENT_H

#include <memory>

#include "Statement.h"

class LoxStatementVisitor;

class BlockStatement : public Statement {
public:
  BlockStatement(std::shared_ptr<Statement> statement);

  void accept(LoxStatementVisitor& visitor);

  std::shared_ptr<Statement> statement;
};

#endif
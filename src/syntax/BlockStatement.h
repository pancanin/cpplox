#ifndef SRC_SYNTAX_BLOCK_STATEMENT_H
#define SRC_SYNTAX_BLOCK_STATEMENT_H

#include <memory>
#include <vector>

#include "Statement.h"

class LoxStatementVisitor;

class BlockStatement : public Statement {
public:
  BlockStatement(std::vector<std::shared_ptr<Statement>> statements);

  void accept(LoxStatementVisitor& visitor);

  std::vector<std::shared_ptr<Statement>> statements;
};

#endif
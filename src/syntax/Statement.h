#ifndef SRC_SYNTAX_STATEMENT_H
#define SRC_SYNTAX_STATEMENT_H

#include "src/syntax/LoxStatementVisitor.h"

class Statement {
public:
  virtual void accept(LoxStatementVisitor&) = 0;
  virtual ~Statement() {};
};

#endif // !SRC_SYNTAX_STATEMENT_H

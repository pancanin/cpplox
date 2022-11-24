#ifndef SRC_SYNTAX_STATEMENT_H
#define SRC_SYNTAX_STATEMENT_H

class LoxStatementVisitor;

class Statement {
public:
  virtual void accept(LoxStatementVisitor&) = 0;
  virtual ~Statement() {};
};

#endif // !SRC_SYNTAX_STATEMENT_H

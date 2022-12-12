#ifndef SRC_SYNTAX_EXPRVISITOR_H_
#define SRC_SYNTAX_EXPRVISITOR_H_

class BinaryExpr;
class LiteralExpr;
class UnaryExpr;
class GroupingExpr;
class AssignmentExpr;
class LogicalExpr;

template <typename R>
class ExprVisitor {
public:
  virtual R visitLiteralExpr(LiteralExpr&) = 0;
  virtual R visitUnaryExpr(UnaryExpr&) = 0;
  virtual R visitBinaryExpr(BinaryExpr&) = 0;
  virtual R visitLogicalExpr(LogicalExpr&) = 0;
  virtual R visitGroupingExpr(GroupingExpr&) = 0;
  virtual R visitAssignExpr(AssignmentExpr&) = 0;

  virtual ~ExprVisitor() = default;
};

#endif /* SRC_SYNTAX_EXPRVISITOR_H_ */

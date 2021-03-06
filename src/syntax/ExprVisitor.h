#ifndef SRC_SYNTAX_EXPRVISITOR_H_
#define SRC_SYNTAX_EXPRVISITOR_H_

struct BinaryExpr;
struct LiteralExpr;
struct UnaryExpr;
struct GroupingExpr;

template <typename R>
class ExprVisitor {
public:
  virtual R visitBinaryExpr(BinaryExpr&) = 0;
  virtual R visitLiteralExpr(LiteralExpr&) = 0;
  virtual R visitUnaryExpr(UnaryExpr&) = 0;
  virtual R visitGroupingExpr(GroupingExpr&) = 0;

  virtual ~ExprVisitor() = default;
};


#endif /* SRC_SYNTAX_EXPRVISITOR_H_ */

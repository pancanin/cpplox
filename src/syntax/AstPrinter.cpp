#include "AstPrinter.h"

#include "src/syntax/BinaryExpr.h"
#include "src/syntax/LiteralExpr.h"
#include "src/syntax/UnaryExpr.h"
#include "src/syntax/GroupingExpr.h"
#include "src/scanner/Token.h"

std::string AstPrinter::print(Expr& expr) {
	return expr.accept(*this);
}

std::string AstPrinter::visitBinaryExpr(BinaryExpr& biExpr) {
	return parentesize(biExpr.operand.lexeme, {biExpr.left, biExpr.right});
}

std::string AstPrinter::visitLiteralExpr(LiteralExpr& expr) {
	return expr.value.lexeme;
}

std::string AstPrinter::visitUnaryExpr(UnaryExpr& expr) {
	return parentesize(expr.op.lexeme, {expr.expr});
}

std::string AstPrinter::visitGroupingExpr(GroupingExpr& expr) {
	return parentesize("group", {expr.expr});
}

std::string AstPrinter::parentesize(std::string name, std::initializer_list<std::shared_ptr<Expr>> expressions) {
	std::string p;

	p += "(" + name;

	for (auto e : expressions) {
		p += " ";
		p += e->accept(*this);
	}

	p += ")";

	return p;
}

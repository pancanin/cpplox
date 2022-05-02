#include <iostream>

#include <cstdint>
#include <string>

#include "src/logging/StdLogger.h"
#include "src/Main.h"

#include "src/logging/StdLogger.h"
#include "src/logging/LangErrorLogger.h"

#include "src/scanner/Token.h"
#include "src/syntax/BinaryExpr.h"
#include "src/syntax/UnaryExpr.h"
#include "src/syntax/LiteralExpr.h"
#include "src/syntax/AstPrinter.h"

int32_t main(int32_t argc, char **argv) {
	LiteralExpr a = LiteralExpr(Token(TokenType::NUMBER, "1", "1", 1));
	Token op = Token(TokenType::PLUS, "+", "+", 1);

	Token unOp = Token(TokenType::MINUS, "-", "-", 1);
	LiteralExpr b = LiteralExpr(Token(TokenType::NUMBER, "2", "2", 1));

	UnaryExpr c = UnaryExpr(unOp, b);

	Expr* expr = new BinaryExpr(
			a,
			op,
			c
	);

	AstPrinter p = AstPrinter();

	std::string res = p.print(*expr);

	std::cout << res << std::endl;
//  const int32_t INVALID_COMMAND_CODE = 64;
//  StdLogger stdLogger;
//  LangErrorLogger errorLogger(stdLogger);
//  Main main(stdLogger, errorLogger);
//
//  if (argc > 2) {
//    stdLogger.info("Correct usage: cpplox [script] or just cpplox for REPL");
//
//    return INVALID_COMMAND_CODE;
//  } else if (argc == 2) {
//    std::string fileName(argv[1]);
//
//    main.runFile(fileName);
//
//    if (errorLogger.hasError()) {
//      return INVALID_COMMAND_CODE;
//    }
//  } else {
//    main.runREPL();
//  }

  return 0;
}

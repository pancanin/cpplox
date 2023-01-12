cmake_minimum_required(VERSION 3.5.1)

function(set_target_cpp_standard target standard)
set_target_properties(
    ${target}
    PROPERTIES
        CXX_STANDARD ${standard}
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
endfunction()

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(cpplox LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
	${DIR}/main.cpp
	${DIR}/src/Main.h
	${DIR}/src/Main.cpp
	${DIR}/src/logging/Logger.h
	${DIR}/src/logging/StdLogger.h
	${DIR}/src/logging/StdLogger.cpp
	${DIR}/src/logging/LangErrorLogger.h
	${DIR}/src/logging/LangErrorLogger.cpp
	${DIR}/src/scanner/TokenType.h
	${DIR}/src/scanner/Scanner.h
	${DIR}/src/scanner/Scanner.cpp
	${DIR}/src/scanner/Token.h
	${DIR}/src/scanner/Token.cpp
	${DIR}/src/syntax/Expr.h
	${DIR}/src/syntax/ToStringExprVisitor.h
	${DIR}/src/syntax/BinaryExpr.h
	${DIR}/src/syntax/LiteralExpr.h
	${DIR}/src/syntax/AstPrinter.h
	${DIR}/src/syntax/AstPrinter.cpp
	${DIR}/src/syntax/ExprVisitor.h
	${DIR}/src/syntax/Statement.h
	${DIR}/src/syntax/PrintStatement.h
	${DIR}/src/syntax/PrintStatement.cpp
	${DIR}/src/syntax/ExprStatement.h
	${DIR}/src/syntax/ExprStatement.cpp
	${DIR}/src/syntax/StatementVisitor.h
	${DIR}/src/syntax/LoxStatementVisitor.h
	${DIR}/src/syntax/BlockStatement.h
	${DIR}/src/syntax/BlockStatement.cpp
	${DIR}/src/syntax/VarStatement.h
	${DIR}/src/syntax/VarStatement.cpp
	${DIR}/src/syntax/IfElseStatement.h
	${DIR}/src/syntax/IfElseStatement.cpp
	${DIR}/src/syntax/LogicalExpr.h
	${DIR}/src/syntax/LogicalExpr.cpp
	${DIR}/src/syntax/CallExpr.h
	${DIR}/src/syntax/CallExpr.cpp
	${DIR}/src/syntax/WhileStatement.h
	${DIR}/src/syntax/WhileStatement.cpp

	${DIR}/src/env/Environment.h
	${DIR}/src/env/Environment.cpp
	
	${DIR}/src/parser/Parser.h
	${DIR}/src/parser/Parser.cpp
	${DIR}/src/parser/ParseError.h
	
	${DIR}/src/interpreter/LoxType.h
	${DIR}/src/interpreter/LoxValueExprVisitor.h
	
	${DIR}/src/interpreter/LoxCallable.h

	${DIR}/src/nativefuncs/TimeFunc.h

	${DIR}/src/interpreter/RuntimeError.h
	${DIR}/src/interpreter/Interpreter.h
	${DIR}/src/interpreter/Interpreter.cpp)
	
set_target_cpp_standard(${PROJECT_NAME} 17)

target_include_directories(${PROJECT_NAME} PRIVATE ${DIR})
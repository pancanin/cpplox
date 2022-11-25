#ifndef SRC_INTERPRETER_LOXVALUE_H_
#define SRC_INTERPRETER_LOXVALUE_H_

#include <string>

#include "src/interpreter/LoxType.h"

struct LoxValue {
	LoxValue() : type(LoxType::NIL) {}
	LoxValue(LoxType type, const std::string& value): type(type), value(value) {}
	LoxValue(bool boolCondition): type(LoxType::BOOLEAN), value(boolCondition ? "true" : "false") {}

	LoxType type;
	std::string value;
};

#endif /* SRC_INTERPRETER_LOXVALUE_H_ */

#ifndef SRC_INTERPRETER_LOXVALUE_H_
#define SRC_INTERPRETER_LOXVALUE_H_

#include <string>

#include "src/interpreter/LoxType.h"

struct LoxValue {
	LoxValue(LoxType type, const std::string& value): type(type), value(value) {}

	LoxType type;
	std::string value;
};

#endif /* SRC_INTERPRETER_LOXVALUE_H_ */

#ifndef SRC_INTERPRETER_LOXVALUE_H_
#define SRC_INTERPRETER_LOXVALUE_H_

#include <string>
#include <memory>

#include "src/interpreter/LoxType.h"

class LoxInstance;

struct LoxValue {
	LoxValue() : type(LoxType::NIL), value(""), instance(nullptr) {}
	LoxValue(LoxType type, const std::string& value): type(type), value(value), instance(nullptr) {}
	LoxValue(bool boolCondition): type(LoxType::BOOLEAN), value(boolCondition ? "true" : "false"), instance(nullptr) {}
	LoxValue(LoxInstance* inst);

	bool isTruthy() const {
		if (type == LoxType::BOOLEAN) {
			return value == "true";
		}
		else if (type == LoxType::NUMBER) {
			return value != "0";
		}
		else if (type == LoxType::STRING) {
			return !value.empty();
		}
		else if (type == LoxType::OBJECT) {
			return instance != nullptr;
		}

		return false;
	}

	LoxType type;
	std::string value;
	LoxInstance* instance;
};

#endif /* SRC_INTERPRETER_LOXVALUE_H_ */

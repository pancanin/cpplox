#ifndef SRC_INTERPRETER_LOXVALUE_H_
#define SRC_INTERPRETER_LOXVALUE_H_

#include <string>
#include <memory>

#include "src/interpreter/LoxType.h"
#include "src/interpreter/LoxInstance.h"

struct LoxValue {
	LoxValue() : type(LoxType::NIL) {}
	LoxValue(LoxType type, const std::string& value): type(type), value(value) {}
	LoxValue(bool boolCondition): type(LoxType::BOOLEAN), value(boolCondition ? "true" : "false") {}
	LoxValue(std::shared_ptr<LoxInstance> inst) : type(LoxType::OBJECT), value(""), instance(inst) {}

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
	std::shared_ptr<LoxInstance> instance;
};

#endif /* SRC_INTERPRETER_LOXVALUE_H_ */

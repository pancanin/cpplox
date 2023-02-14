#ifndef INTERPRETER_LOX_INSTANCE_H
#define INTERPRETER_LOX_INSTANCE_H

#include <string>
#include <unordered_map>
#include <memory>

#include "src/interpreter/LoxValue.h"

class LoxClass;

class LoxInstance {
public:
	LoxInstance(LoxClass& klass);

	std::string to_string() const;

	LoxValue get(const std::string& name);
	void set(const std::string& name, const LoxValue& val);

	LoxClass& klass;
	std::unordered_map<std::string, LoxValue> fields;
};

#endif // !INTERPRETER_LOX_INSTANCE_H

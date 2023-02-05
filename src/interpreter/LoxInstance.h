#ifndef INTERPRETER_LOX_INSTANCE_H
#define INTERPRETER_LOX_INSTANCE_H

#include <string>
#include <unordered_map>
#include <memory>

class LoxValue;
class LoxClass;

class LoxInstance {
public:
	LoxInstance(LoxClass& klass);

	std::string to_string() const;

	LoxValue* get(const std::string& name);

	LoxClass& klass;
	std::unordered_map<std::string, LoxValue*> fields;
};

#endif // !INTERPRETER_LOX_INSTANCE_H

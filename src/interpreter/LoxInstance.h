#ifndef INTERPRETER_LOX_INSTANCE_H
#define INTERPRETER_LOX_INSTANCE_H

#include <string>

class LoxClass;

class LoxInstance {
public:
	LoxInstance(LoxClass& klass);

	std::string to_string() const;
private:
	LoxClass& klass;
};

#endif // !INTERPRETER_LOX_INSTANCE_H

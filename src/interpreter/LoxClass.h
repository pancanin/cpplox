#ifndef INTERPRETER_LOX_CLASS_H
#define INTERPRETER_LOX_CLASS_H

#include <string>
#include <memory>
#include <vector>

#include "LoxCallable.h"
#include "LoxInstance.h"
#include "src/syntax/Statement.h"

class LoxClass {
public:
  LoxClass(const std::string& name, std::vector<std::shared_ptr<Statement>> methods) : name(name), methods(methods) {}

  std::shared_ptr<LoxInstance> instantiate(Interpreter* interpreter, std::vector<LoxValue> args);

  uint32_t arity() {
    return 0; // Later, with ctors, there could be more
  }

  std::string toString() const {
    return name;
  }

  std::string name;
  std::vector<std::shared_ptr<Statement>> methods;
};

#endif // !INTERPRETER_LOX_CLASS_H

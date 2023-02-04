#ifndef INTERPRETER_LOX_CLASS_H
#define INTERPRETER_LOX_CLASS_H

#include <string>
#include <memory>

#include "LoxCallable.h"
#include "LoxInstance.h"

class LoxClass {
public:
  LoxClass(const std::string& name) : name(name) {}

  std::shared_ptr<LoxInstance> instantiate(Interpreter* interpreter, std::vector<LoxValue> args) {
    auto instance = std::make_shared <LoxInstance>(*this);
    return instance;
  }

  uint32_t arity() {
    return 0; // Later, with ctors, there could be more
  }

  std::string toString() const {
    return name;
  }

  std::string name;
};

#endif // !INTERPRETER_LOX_CLASS_H

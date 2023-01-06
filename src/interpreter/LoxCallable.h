#ifndef INTERPRETER_LOX_CALLABLE_H
#define INTERPRETER_LOX_CALLABLE_H

#include <memory>
#include <vector>

#include "Interpreter.h"
#include "LoxValue.h"

class LoxCallable {
public:
  virtual LoxValue call(std::shared_ptr<Interpreter>, std::vector<LoxValue> args) = 0;
  virtual uint32_t arity() = 0;
};

#endif // !INTERPRETER_LOX_CALLABLE_H

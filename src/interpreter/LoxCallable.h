#ifndef INTERPRETER_LOX_CALLABLE_H
#define INTERPRETER_LOX_CALLABLE_H

#include <memory>
#include <vector>

#include "LoxValue.h"

class Interpreter;

class LoxCallable {
public:
  virtual LoxValue call(Interpreter const * const, std::vector<LoxValue> args) = 0;
  virtual uint32_t arity() = 0;
};

#endif // !INTERPRETER_LOX_CALLABLE_H
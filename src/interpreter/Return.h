#ifndef INTERPRETER_RETURN_H
#define INTERPRETER_RETURN_H

#include <exception>

#include "src/interpreter/LoxValue.h"

class Return : public std::exception {
public:
  Return(LoxValue value) : value(value) {}

  LoxValue value;
};

#endif // !INTERPRETER_RETURN_H

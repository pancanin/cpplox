#ifndef SRC_FUNCS_TIME_FUNC_H
#define SRC_FUNCS_TIME_FUNC_H

#include <time.h>
#include "src/interpreter/LoxCallable.h"

class TimeFunc : public LoxCallable {
public:
  LoxValue call(Interpreter const* const interpreter, std::vector<LoxValue> args) {
    // We can create a Date LoxType that is handled in a different way by the console and can have additional methods on it.
    return LoxValue(LoxType::NUMBER, std::to_string(time(0)));
  }
  uint32_t arity() {
    return 0;
  }
};

#endif // !SRC_FUNCS_TIME_FUNC_H

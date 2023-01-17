#ifndef NATIVES_SLUR_FUNC_H
#define NATIVES_SLUR_FUNC_H

#include <unordered_map>

#include "src/interpreter/LoxCallable.h"

class SlurFunc : public LoxCallable {
public:
  LoxValue call(Interpreter* interpreter, std::vector<LoxValue> args) {
    std::unordered_map<std::string, std::string> slurs = {
      { "0", "Go 'a hell!" },
      { "1", "You prick!" },
      { "2", "Shenjkobarioiii!!!!" }
    };

    return LoxValue(LoxType::STRING, slurs[args[0].value]);
  }

  uint32_t arity() {
    return 1;
  }
};

#endif // !NATIVES_SLUR_FUNC_H

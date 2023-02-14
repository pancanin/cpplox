#include "LoxClass.h"

#include "src/interpreter/Interpreter.h"

std::shared_ptr<LoxInstance> LoxClass::instantiate(Interpreter* interpreter, std::vector<LoxValue> args) {
  auto instance = std::make_shared <LoxInstance>(*this);

  interpreter->initInstanceState(instance.get());

  return instance;
}
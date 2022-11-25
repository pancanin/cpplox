#ifndef SRC_ENV_ENVIRONMENT_H
#define SRC_ENV_ENVIRONMENT_H

#include <string>
#include <unordered_map>

#include "src/interpreter/LoxValue.h"

class Environment {
public:
  void declareVariable(std::string name, const LoxValue& value);
private:
  std::unordered_map<std::string, LoxValue> varStorage; // TODO: It is not a great idea for the LoxValue to be copied left and right...
};

#endif // !SRC_ENV_ENVIRONMENT_H

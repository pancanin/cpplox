#include "Environment.h"

void Environment::declareVariable(std::string name, const LoxValue& value)
{
  varStorage[name] = value;
}

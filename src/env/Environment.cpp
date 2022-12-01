#include "Environment.h"

void Environment::declareVariable(const std::string& name, const LoxValue& value)
{
  varStorage[name] = value;
}

LoxValue Environment::evalVariable(const std::string& name)
{
  return varStorage[name];
}

bool Environment::declaresVariable(const std::string& name)
{
  return varStorage.find(name) != varStorage.end();
}

void Environment::clear()
{
  varStorage.clear();
}

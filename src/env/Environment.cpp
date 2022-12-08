#include "Environment.h"

Environment::Environment(): parent(nullptr)
{
}

Environment::Environment(std::shared_ptr<Environment> parent): parent(parent)
{
}

void Environment::declareVariable(const std::string& name, const LoxValue& value)
{
  varStorage[name] = value;
}

bool Environment::assignVariable(const std::string& name, const LoxValue& value)
{
  if (declaresVariable(name)) {
    varStorage[name] = value;
    return true;
  }

  if (parent != nullptr) {
    return parent->assignVariable(name, value);
  }

  return false;
}

LoxValue Environment::evalVariable(const std::string& name)
{
  if (declaresVariable(name)) {
    return varStorage[name];
  }

  if (parent != nullptr) {
    return parent->evalVariable(name);
  }

  return LoxValue();
}

bool Environment::declaresVariable(const std::string& name)
{
  return varStorage.find(name) != varStorage.end();
}

void Environment::clear()
{
  varStorage.clear();
}

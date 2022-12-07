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
  // Check if the variable is in the current scope
  // Yes - Then just update it and return true
  // No:
  //     - Do we have a parent scope?
  //        - Yes - Call assignVariable recursively on the parent scope
  //        - No - return false, as this variable has not been declared
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

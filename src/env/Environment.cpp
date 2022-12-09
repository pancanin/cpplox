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
  if (doesCurrentEnvDeclareVariable(name)) {
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
  if (doesCurrentEnvDeclareVariable(name)) {
    return varStorage[name];
  }

  if (parent != nullptr) {
    return parent->evalVariable(name);
  }

  return LoxValue();
}

bool Environment::doesCurrentEnvDeclareVariable(const std::string& name)
{
  return varStorage.find(name) != varStorage.end();
}

bool Environment::resolveVariableDeclaration(const std::string& name)
{
  if (parent == nullptr) {
    return doesCurrentEnvDeclareVariable(name);
  }

  return parent->resolveVariableDeclaration(name);
}

void Environment::clear()
{
  varStorage.clear();
}

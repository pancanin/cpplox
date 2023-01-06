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
  return doesCurrentEnvDeclareVariable(name) || parent->resolveVariableDeclaration(name);
}

void Environment::clear()
{
  varStorage.clear();
}

void Environment::define(const std::string& name, std::shared_ptr<LoxCallable> callable)
{
  functionStorage[name] = callable;
}

std::shared_ptr<LoxCallable> Environment::resolveFunction(const std::string& name)
{
  if (hasEnvGotFunction(name)) {
    return functionStorage[name];
  }

  if (parent != nullptr) {
    return parent->resolveFunction(name);
  }

  return nullptr;
}

bool Environment::hasEnvGotFunction(const std::string& name)
{
  return functionStorage.find(name) != functionStorage.end();
}

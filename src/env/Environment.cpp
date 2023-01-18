#include "Environment.h"

Environment::Environment(): parent(nullptr)
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
  return doesCurrentEnvDeclareVariable(name) || (parent && parent->resolveVariableDeclaration(name));
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
  if (hasCurrentEnvGotFunction(name)) {
    return functionStorage[name];
  }

  if (parent != nullptr) {
    return parent->resolveFunction(name);
  }

  return nullptr;
}

bool Environment::hasCurrentEnvGotFunction(const std::string& name)
{
  return functionStorage.find(name) != functionStorage.end();
}

bool Environment::hasFunction(const std::string& name)
{
  if (hasCurrentEnvGotFunction(name)) {
    return true;
  }

  return parent != nullptr && parent->hasFunction(name);
}

void Environment::declareFunc(std::shared_ptr<FuncStatement> funcStmt)
{
  functionStorage[funcStmt->name.literal] = funcStmt;
}

void Environment::setParent(std::shared_ptr<Environment> parentEnv)
{
  this->parent = parentEnv;
}

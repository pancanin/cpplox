#ifndef SRC_ENV_ENVIRONMENT_H
#define SRC_ENV_ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include <memory>

#include "src/interpreter/LoxValue.h"
#include "src/interpreter/LoxCallable.h"
#include "src/interpreter/LoxClass.h"

class Environment {
public:
  Environment();

  void declareVariable(const std::string& name, const LoxValue& value);

  /// <summary>
  /// Resolves a variable, first in current scope then in parent.
  /// Updates the variable with a new value, no matter if it is found in current scope or any parent scope.
  /// </summary>
  /// <param name="name">The identifier of the variable</param>
  /// <param name="value">The value of the variable</param>
  /// <returns>Returns a boolean - if the variable is found and updated it returns true, otherwise false.</returns>
  bool assignVariable(const std::string& name, const LoxValue& value);
  LoxValue evalVariable(const std::string& name);
  bool doesCurrentEnvDeclareVariable(const std::string& name);
  bool resolveVariableDeclaration(const std::string& name);
  void clear();

  // Function related methods
  // The 'define' function can accept a lambda and a number of arguments, so the clients can easily construct LoxCallables
  void define(const std::string& name, std::shared_ptr<LoxCallable> callable);
  std::shared_ptr<LoxCallable> resolveFunction(const std::string& name);
  bool hasFunction(const std::string& name);

  void setParent(std::shared_ptr<Environment> parentEnv);

  void declareClass(std::shared_ptr<LoxClass> klass);
  std::shared_ptr<LoxClass> getClass(const std::string& className);
  
  std::shared_ptr<Environment> parent;
private:
  std::unordered_map<std::string, LoxValue> varStorage;
  std::unordered_map<std::string, std::shared_ptr<LoxCallable>> functionStorage;
  std::unordered_map<std::string, std::shared_ptr<LoxClass>> classStorage;

  bool hasCurrentEnvGotFunction(const std::string& name);
};

#endif // !SRC_ENV_ENVIRONMENT_H

#ifndef SRC_ENV_ENVIRONMENT_H
#define SRC_ENV_ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include <memory>

#include "src/interpreter/LoxValue.h"
#include "src/interpreter/LoxCallable.h"
#include "src/syntax/FuncStatement.h"

class Environment {
public:
  Environment();
  Environment(std::shared_ptr<Environment> parent);

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
  bool hasEnvGotFunction(const std::string& name);

  void declareFunc(std::shared_ptr<FuncStatement> funcStmt);
  
  std::shared_ptr<Environment> parent;
private:
  std::unordered_map<std::string, LoxValue> varStorage;
  std::unordered_map<std::string, std::shared_ptr<LoxCallable>> functionStorage;
};

#endif // !SRC_ENV_ENVIRONMENT_H

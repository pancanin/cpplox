#ifndef SRC_ENV_ENVIRONMENT_H
#define SRC_ENV_ENVIRONMENT_H

#include <string>
#include <unordered_map>
#include <memory>

#include "src/interpreter/LoxValue.h"

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
  bool declaresVariable(const std::string& name);
  void clear();

  std::shared_ptr<Environment> parent;
private:
  std::unordered_map<std::string, LoxValue> varStorage; // TODO: It is not a great idea for the LoxValue to be copied left and right...
};

#endif // !SRC_ENV_ENVIRONMENT_H

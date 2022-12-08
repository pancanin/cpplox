#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <string>
#include <cstdint>
#include <memory>

#include "src/logging/LangErrorLogger.h"
#include "src/logging/Logger.h"
#include "src/env/Environment.h"

/// <summary>
/// Entrypoint class for the whole cpplox program.
/// </summary>
class Main {
public:
  Main(Logger&, LangErrorLogger&);

  /// <summary>
  /// Loads a file and runs the interpreter over each line of code.
  /// </summary>
  /// <param name="filePath">The path to the file</param>
  void runFile(const std::string& filePath) const;

  /// <summary>
  /// Runs a Read, Eval, Print Loop for interactive scripting.
  /// </summary>
  void runREPL();
private:
  Logger& logger;
  LangErrorLogger& langErrorLogger;
  std::shared_ptr<Environment> env;

  /// <summary>
  /// Helper method that receives source code and runs it through the interpreter. Called from runFile and runREPL.
  /// </summary>
  /// <param name="sourceCode">Programming language code in text format.</param>
  void run(const std::string& sourceCode) const;
};

#endif /* SRC_MAIN_H_ */

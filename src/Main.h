#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <string>

class Main {
public:
  void runFile(const std::string& fileName) const;
  void runREPL() const;

private:
  void run(const std::string& sourceCode) const;
};

#endif /* SRC_MAIN_H_ */

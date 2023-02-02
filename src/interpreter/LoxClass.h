#ifndef INTERPRETER_LOX_CLASS_H
#define INTERPRETER_LOX_CLASS_H

#include <string>

class LoxClass {
public:
  LoxClass(const std::string& name) : name(name) {}

  std::string toString() const {
    return name;
  }

  std::string name;
};

#endif // !INTERPRETER_LOX_CLASS_H

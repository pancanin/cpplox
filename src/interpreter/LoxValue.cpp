#include "LoxValue.h"

#include <iostream>

#include "src/interpreter/LoxInstance.h"

using namespace std;

LoxValue::LoxValue(LoxInstance* inst) : type(LoxType::OBJECT), value(inst->to_string()), instance(inst) {
  cout << "What do we have here?" << endl;
}
#include "LoxInstance.h"

#include "LoxClass.h"

#include "src/interpreter/LoxValue.h"

LoxInstance::LoxInstance(LoxClass& klass): klass(klass) {}

 std::string LoxInstance::to_string() const
 {
	 return klass.name + " instance!";
 }

 LoxValue LoxInstance::get(const std::string& name)
 {
	 return fields[name];
 }

 void LoxInstance::set(const std::string& name, const LoxValue& val)
 {
	 fields[name] = val;
 }

#include "LoxInstance.h"

#include "LoxClass.h"

LoxInstance::LoxInstance(LoxClass& klass): klass(klass) {}

 std::string LoxInstance::to_string() const
 {
	 return klass.name + " instance!";
 }

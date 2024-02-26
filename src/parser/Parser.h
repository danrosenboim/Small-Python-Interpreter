#pragma once
#include <iostream>
#include <sstream>
#include "../types/Type.h"
#include "../exceptions/IndentationException.h"
#include "../exceptions/SyntaxException.h"
#include "../exceptions/NameErrorException.h"
#include "../utils/TypeUtils.h"
#include "../types/Integer.h"
#include "../types/Boolean.h"
#include "../types/String.h"
#include <unordered_map>
#include "../types/Void.h"
#include <utility>
#include <set>

class Parser
{
public:
	static Type* parseString(std::string s);
	static Type* getType(std::string s);
	
	static void cleanMemory();

private:
	static std::unordered_map<std::string, Type*> _variables;
	
	static bool isLegalVarName(const std::string& s);
	static bool makeAssignment(const std::string& s);
	static Type* getVariableValue(const std::string& s);

};

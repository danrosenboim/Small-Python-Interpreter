#include "Parser.h"

std::unordered_map<std::string, Type*> Parser::_variables;

Type* Parser::parseString(std::string s)
{
	if(s.length() <= 0)
	{
		return nullptr;
	}
	
	if(s[0] == ' ' || s[0] == '\t')
	{
		throw IndentationException();
	}

	TypeUtils::remWhitespaceEnd(s);
	
	Type* type = getVariableValue(s);
	if(type)
	{
		return type;
	}

	type = getType(s);
	if(type)
	{
		return type;
	}
	
	if(makeAssignment(s))
	{
		return (Type*)(new Void(true));
	}
	
	throw NameErrorException(s);
}

Type* Parser::getType(std::string s)
{
	// removing the whitespace at the start of the input
	TypeUtils::remWhitespaceStart(s);
	if(TypeUtils::isInteger(s))
	{
		return new Integer(std::stoi(s), true);
	}
	else if(s == "True" || s == "False")
	{
		return new Boolean((s == "True"), true);
	}
	else if(s.size() > 1 && (s[0] == '\'' || s[0] == '"') && s.substr(1).find(s[0]) == s.size() - 2)
	{
		s = s.substr(1, s.size() - 2);
		std::vector<char> cArr(s.begin(), s.end());
		return new String(cArr, true);
	}
	return nullptr;
}

bool Parser::isLegalVarName(const std::string& s)
{
	if(!std::isalpha(s[0]))
	{
		return false;
	}
	for(size_t i = 0; i < s.size(); i++)
	{
		if(!std::isdigit(s[i]) && !std::isalpha(s[i]) && s[i] != '_')
		{
			return false;
		}
	}
	return true;
}

bool Parser::makeAssignment(const std::string& s)
{
	std::string varName;
	std::string value;

	size_t pos = s.find('=');
	if(pos == std::string::npos)
	{
		return false;
	}

	varName = s.substr(0, pos);
	TypeUtils::remWhitespaceEnd(varName);
	
	value = s.substr(pos + 1);
	TypeUtils::remWhitespaceStart(value);
	TypeUtils::remWhitespaceEnd(value);

	pos = s.substr(pos + 1).find('=');
	if(pos != std::string::npos)
	{
		return false;
	}
	
	if(!isLegalVarName(varName))
	{
		throw SyntaxException();
	}

	Type* type = getType(value);
	if(!type)
	{
		auto result = _variables.find(value);
		if(result == _variables.end())
		{
			throw SyntaxException();
		}
		type = getType(result->second->toString());
	}
	type->setIsTemp(false);	
	auto result = _variables.find(varName);
	if(result == _variables.end())
	{
		_variables.insert(std::make_pair(varName, type));
	}
	else
	{
		delete result->second;
		_variables.insert_or_assign(varName, type);	
	}
	return true;
}

Type* Parser::getVariableValue(const std::string& s)
{
	auto result = _variables.find(s);
	if(result == _variables.end())
	{
		return nullptr;
	}
	else
	{
		return result->second;
	}

}

void Parser::cleanMemory()
{
    std::set<void*> deletedPointers;

    for(auto& value : _variables)
    {
        
        if(deletedPointers.find(value.second) == deletedPointers.end())
        {
            delete value.second; 
			
			deletedPointers.insert(value.second);
		}
    }
    _variables.clear();
}

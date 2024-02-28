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

	if(s.find("type(") == 0 && s[s.size() - 1] == ')')
	{
		std::string arg = s.substr(5, s.size() - 6);
		type = getVariableValue(arg);
		if(!type)
		{
			type = getType(arg);
			if(!type)
			{
				throw NameErrorException(arg);
			}
		}
		std::cout << "<type '" << type->getType() << "'>" << std::endl;
		return new Void(true);
	}

	if(s.find("del ") == 0)
	{
		std::string arg = s.substr(4);
		type = getVariableValue(arg);
		if(!type)
		{
			throw NameErrorException(arg);
		}
		delete type;
		_variables.erase(arg);
		return new Void(true);
	}
	
	if(s.find("len(") == 0 && s[s.size() - 1] == ')')
	{
		std::string arg = s.substr(4, s.size() - 5);
		type = getVariableValue(arg);
		if(!type)
		{
			type = getType(arg);
			if(!type)
			{
				throw NameErrorException(arg);
			}
		}
		if(type->getType() == "list")
		{
			return new Integer(((Sequence<Type*>*)type)->getLength(), true);
		}
		else if(type->getType() == "str")
		{
			return new Integer(((Sequence<char>*)type)->getLength(), true);
		}
		else
		{
			throw TypeErrorException(type->getType());
		}
	}
	else if(s.find("len") == 0)
	{
		std::cout << "<build-in function len>" << std::endl;
		return new Void(true);
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
	else if(s.size() > 1 && s[0] == '[' && s[s.size() - 1] == ']')
	{
		std::vector<Type*> types;
		std::vector<int> typeLocations;
		
		typeLocations.push_back(0);

		bool inString = false;
		for(size_t i = 0; i < s.size(); i++)
		{
			if(s[i] == '\'' || s[i] == '"')
			{
				inString = !inString;
				continue;
			}
			if(inString)
			{
				continue;
			}
			if(s[i] == ',')
			{
				typeLocations.push_back(i);
			}
		}
		typeLocations.push_back(s.size() - 1);
		for(size_t i = 1; i < typeLocations.size(); i++)
		{
			Type* curType = nullptr;
			std::string typeString = s.substr(typeLocations[i - 1] + 1, typeLocations[i] - (typeLocations[i - 1] + 1));
			if(typeString != "")
			{
				TypeUtils::remWhitespaceStart(typeString);
				TypeUtils::remWhitespaceEnd(typeString);
				curType = getType(typeString);
			}
			if(!curType)
			{
				for(size_t i = 0; i < types.size(); i++)
				{
					delete types[i];
				}
				types.clear();
				return nullptr;
			}
			types.push_back(curType);
		}
		return new List(types, true);
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
		std::string checkList = result->second->toString();
		if(checkList.size() >= 1 && checkList[0] == '[')
		{
			type = result->second;
		}
		else
		{
			type = getType(checkList);
		}
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

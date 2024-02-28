#include "String.h"

String::String(const std::vector<char> s, bool isTemp) : Sequence<char>(s, isTemp)
{}

bool String::isPrintable() const
{
	return true;
}

std::string String::toString() const
{
	std::string output = "'";
	for(int i = 0; i < _value.size(); i++)
	{
		output += _value[i];
	}
	return output + "'";
}

std::string String::getType() const
{
	return "str";
}

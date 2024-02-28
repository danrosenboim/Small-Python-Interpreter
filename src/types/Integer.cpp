#include "Integer.h"

Integer::Integer(int value, bool isTemp) : Type(isTemp), _value(value)
{}

bool Integer::isPrintable() const
{
	return true;
}

std::string Integer::toString() const
{
	return std::to_string(_value);
}

std::string Integer::getType() const
{
	return "int";
}

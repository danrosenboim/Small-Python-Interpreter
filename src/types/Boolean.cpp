#include "Boolean.h"

Boolean::Boolean(bool value, bool isTemp) : Type(isTemp), _value(value)
{}

bool Boolean::isPrintable() const
{
	return true;
}

std::string Boolean::toString() const
{
	if(_value)
	{
		return "True";
	}
	return "False";
}

#include "List.h"

List::List(const std::vector<Type*> types, bool isTemp) : Sequence<Type*>(types, isTemp)
{}

List::~List()
{
	for(size_t i = 0; i < _value.size(); i++)
	{
		delete _value[i];
	}
}

bool List::isPrintable() const
{
	return true;
}

std::string List::toString() const
{
	std::stringstream str;
	str << '[';
	for(size_t i = 0; i < _value.size(); i++)
	{
		if(i != 0)
		{
			str << ", ";
		}
		str << _value[i]->toString();
	}
	str << ']';
	return str.str();
}

std::string List::getType() const
{
	return "list";
}

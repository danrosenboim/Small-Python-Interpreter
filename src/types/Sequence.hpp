#pragma once
#include "Type.h"
#include <vector>

template<typename T>
class Sequence : public Type
{
public:
	Sequence(std::vector<T> seq, bool isTemp);
	
	virtual bool isPrintable() const = 0;
	virtual std::string toString() const = 0;
	int getLength() const;
protected:
	std::vector<T> _value;
};

template<typename T>
Sequence<T>::Sequence(std::vector<T> seq, bool isTemp) : Type(isTemp)
{
	_value = seq;
}

template<typename T>
int Sequence<T>::getLength() const
{
	return _value.size();
}

#include "Type.h"

Type::Type() : _isTemp(false) {}

Type::Type(bool isTemp) : _isTemp(isTemp) {}

bool Type::getIsTemp() const
{
	return _isTemp;
}

void Type::setIsTemp(bool isTemp)
{
	_isTemp = isTemp;
}

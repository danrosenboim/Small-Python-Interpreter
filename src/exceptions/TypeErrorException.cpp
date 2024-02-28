#include "TypeErrorException.h"

TypeErrorException::TypeErrorException(const std::string& error)
{
	_message = "TypeError: object of type'" + error + " has no len().";
}

const char* TypeErrorException::what() const noexcept
{
	return _message.c_str();
}

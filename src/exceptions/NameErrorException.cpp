#include "NameErrorException.h"

NameErrorException::NameErrorException(const std::string& error)
{
	_message = "NameError: name '" + error + "' is not defined";
}

const char* NameErrorException::what() const noexcept
{
	return _message.c_str();
}

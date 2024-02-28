#pragma once
#include "Exception.h"
#include <sstream>


class TypeErrorException : public Exception
{
public:
	TypeErrorException(const std::string& error);
	virtual const char* what() const noexcept;

private:
	std::string _message;	
};

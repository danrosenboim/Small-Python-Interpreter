#pragma once
#include "Exception.h"
#include <sstream>


class NameErrorException : public Exception
{
public:
	NameErrorException(const std::string& error);
	virtual const char* what() const noexcept;

private:
	std::string _message;	
};

#pragma once
#include "Exception.h"

class SyntaxException : public Exception
{
public:
	virtual const char* what() const noexcept;
};

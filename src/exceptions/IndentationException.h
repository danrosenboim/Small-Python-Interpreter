#pragma once
#include "Exception.h"

class IndentationException : public Exception
{
public:
	virtual const char* what() const noexcept;
};

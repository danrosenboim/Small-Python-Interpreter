#include "TypeUtils.h"

bool TypeUtils::isInteger(const std::string& s)
{
	int start = (s[0] == '-') ? 1 : 0;
	for(size_t i = start; i < s.size(); i++)
	{
		if(!std::isdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}

void TypeUtils::remWhitespaceStart(std::string& s)
{
	size_t startPos = s.find_first_not_of(" \t");
	if(std::string::npos != startPos)
	{
		s = s.substr(startPos);
	}
}

void TypeUtils::remWhitespaceEnd(std::string& s)
{
	size_t endPos = s.find_last_not_of(" \t");
	if (std::string::npos != endPos)
	{
		s = s.substr(0, endPos + 1);
	}
}



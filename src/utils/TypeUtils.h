#pragma once
#include <iostream>
#include <string>
#include <vector>

class TypeUtils
{
public:
	static bool isInteger(const std::string& s);
	static void remWhitespaceStart(std::string& s);
	static void remWhitespaceEnd(std::string& s);
};

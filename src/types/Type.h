#pragma once
#include <iostream>
#include <string>

class Type
{
public:
	Type();
	Type(bool isTemp);

	virtual ~Type() = default;

	// getters
	bool getIsTemp() const;

	// setters
	void setIsTemp(bool isTemp);

	virtual bool isPrintable() const = 0;

	virtual std::string toString() const = 0;
private:
	bool _isTemp;
};

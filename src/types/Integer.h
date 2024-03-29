#pragma once
#include "Type.h"

class Integer : public Type
{
public:
	Integer(int value, bool isTemp);

	virtual bool isPrintable() const override;
	virtual std::string toString() const override;
	virtual std::string getType() const override;
	
private:
	int _value;
};

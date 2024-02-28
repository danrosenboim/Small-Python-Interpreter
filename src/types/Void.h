#pragma once
#include "Type.h"

class Void : public Type
{
public:
	Void(bool isTemp);
	virtual ~Void() override = default;

	virtual bool isPrintable() const override;
	virtual std::string toString() const override;
	virtual std::string getType() const override;
};

#pragma once
#include "Sequence.hpp"

class String : public Sequence<char>
{
public:
	String(const std::vector<char> s, bool isTemp);

	virtual bool isPrintable() const override;
	virtual std::string toString() const override;
	virtual std::string getType() const override;
};

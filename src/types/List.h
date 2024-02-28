#pragma once
#include "Sequence.hpp"
#include <sstream>

class List : public Sequence<Type*>
{
public:
	List(const std::vector<Type*> types, bool isTemp);
	virtual ~List() override;

	virtual bool isPrintable() const override;
	virtual std::string toString() const override;
	virtual std::string getType() const override;	
};

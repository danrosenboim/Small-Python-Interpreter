#include <iostream>
#include "parser/Parser.h"
#include "exceptions/IndentationException.h"

#define WELCOME "Welcome to my Python Interpreter version 1.0"

int main()
{
	std::cout << WELCOME << std::endl;
	std::string inputString;

	// Get input from user
	std::cout << ">>> ";
	std::getline(std::cin, inputString);

	while(inputString != "quit()")
	{
		// Parsing the user command
		try
		{
			Type* type = Parser::parseString(inputString);
			if(type->isPrintable())
			{
				std::cout << type->toString() << std::endl;
			}
			if(type->getIsTemp())
			{
				delete type;
			}
		}
		catch(IndentationException& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch(SyntaxException& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch(NameErrorException& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch(TypeErrorException& e)
		{
			std::cout << e.what() << std::endl;
		}

		// Get input from user
		std::cout << ">>> ";
		std::getline(std::cin, inputString);
	}

	Parser::cleanMemory();

	return 0;
}

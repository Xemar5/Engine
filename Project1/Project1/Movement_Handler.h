#pragma once
#include <string>

class Movement_Handler
{
public:
	template <typename T>
	static bool Set(std::string modifier, T... elem);
	template <typename T, typename ... Args>
	static bool Set(std::string modifier, T elem, Args... arg_list);
private:
	template <typename T>
	static bool __Type_Deduce(char type, T elem);
};

#include <iostream>

template <typename T>
bool Movement_Handler::Set(std::string modifier, T elem)
{
	if (!modifier.size())
	{
		std::cerr << "ERR Movement_Handler::Set : No modifier supplied" << std::endl;
		return false;
	}

	char c = modifier.front();
	if (!__Type_Deduce(c, elem))
	{
		std::cerr << "ERR Movement_Handler::Set : Couldn't deduce the type\n";
		return false;
	}
	return true;
}

template<typename T, typename ...Args>
bool Movement_Handler::Set(std::string modifier, T elem, Args ...arg_list)
{
	if (!modifier.size())
	{
		std::cerr << "ERR Movement_Handler::Set : No modifier supplied" << std::endl;
		return false;
	}
	if (modifier.size() < sizeof...(arg_list) + 1)
	{
		std::cerr << "ERR Movement_Handler::Set : Unequal size of parameters; modifier size - " << modifier.size() << ", no. arguments - " << sizeof...(arg_list)+1 << std::endl;
		return false;
	}
	if (modifier.size() > sizeof...(arg_list) + 1)
	{
		std::cout << "MSG Movement_Handler::Set : Modifier gives more information than the number of parameters\n";
	}

	char c = modifier.front();
	modifier.erase(modifier.begin());
	if (!__Type_Deduce(c, elem))
	{
		std::cerr << "ERR Movement_Handler::Set : Couldn't deduce the type\n";
		return false;
	}

	return Movement_Handler::Set(modifier, arg_list);
}

template<typename T>
bool Movement_Handler::__Type_Deduce(char type, T elem)
{
	switch (type)
	{
	case 'a':
		return true;
	default:
		std::cerr << "ERR Movement_Handler::__Type_Deduce : Coundn't deduce the '"<< type <<"' type\n";
		return false;
	}
	return false;
}

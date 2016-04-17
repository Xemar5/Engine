#include "Input_Handler.h"
#include "Keyboard_Handler.h"
#include "Gamepad_Handler.h"
#include "Mouse_Handler.h"
#include "Player.h"
#include <iostream>

std::shared_ptr<Input_Handler> Input_Handler::Set(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32> arg_list)
{
	if (!input_foo)
	{
		std::cerr << "ERR Input_Handler::Set : No Input Function supplied\n";
		return nullptr;
	}
	if (!arg_list.size())
	{
		std::cerr << "ERR Input_Handler::Set : No Arg List supplied\n";
		return nullptr;
	}

	std::shared_ptr<Input_Handler> ih = std::make_shared<Input_Handler>();
	ih->__Input_Function = input_foo;
	ih->__Arg_List = arg_list;

	return ih;
}



double Input_Handler::Check()
{
	if (!this)
	{
		std::cerr << "ERR Input_Handler::Check : No Input Handler Initialized\n";
		return 0.0;
	}
	if (!__Input_Function)
	{
		std::cerr << "ERR Input_Handler::Check : No Input Function supplied\n";
		return 0.0;
	}
	return __Input_Function(__Arg_List);
}

bool Input_Handler::Change_Input_Function(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32> arg_list)
{
	if(!input_foo)
	{
		std::cout << "MSG Input_Handler::Change_Input_Function : No input foo supplied; if only arg list intended, use Input_Handler::Change_Arg_List\n";
	}
	else __Input_Function = input_foo;
	if (arg_list.size())
	{
		__Arg_List = arg_list;
	}
	return true;
}

bool Input_Handler::Change_Arg_List(std::vector<Sint32> arg_list)
{
	if (!arg_list.size())
	{
		std::cerr << "ERR Input_Handler::Change_Arg_List : No arg list supplied\n";
		return false;
	}
	__Arg_List = arg_list;
	return true;
}

void Input_Handler::__Update()
{
	Keyboard_Handler::__Update();
	Mouse_Handler::__Update();
	Gamepad_Handler::__Update();
	Player::__Update();
}

void Input_Handler::__Events()
{
	Keyboard_Handler::__Events();
	Mouse_Handler::__Events();
	Gamepad_Handler::__Events();
	Player::__Events();
}

#include "Input_Handler.h"
#include "Keyboard_Handler.h"
#include "Gamepad_Handler.h"
#include "Mouse_Handler.h"
#include "Player.h"
#include <iostream>

Input_Function Input_Handler::Set(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32> arg_list)
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

	Input_Function ih = std::make_shared<Input_Handler>();
	ih->__Input_Function = input_foo;
	std::vector<std::shared_ptr<Sint32>> v(arg_list.size());
	for (unsigned i = 0; i < arg_list.size(); i++)
		v[i] = std::make_shared<Sint32>(arg_list[i]);
	ih->__Arg_List = v;
	return ih;
}



Input_Function Input_Handler::Set_Dynamic(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32*> arg_list)
{
	if (!input_foo)
	{
		std::cerr << "ERR Input_Handler::Set_Dynamic : No Input Function supplied\n";
		return nullptr;
	}
	if (!arg_list.size())
	{
		std::cerr << "ERR Input_Handler::Set_Dynamic : No Arg List supplied\n";
		return nullptr;
	}

	Input_Function ih = std::make_shared<Input_Handler>();
	ih->__Input_Function = input_foo;
	std::vector<std::shared_ptr<Sint32>> v(arg_list.size());
	for (unsigned i = 0; i < arg_list.size(); i++)
	{
		if (!arg_list[i]) continue;
		v[i] = std::shared_ptr<Sint32>(arg_list[i], [](Sint32*) {});
	}
	ih->__Arg_List = v;

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
	std::vector<Sint32> v(__Arg_List.size());
	for (unsigned i = 0; i < __Arg_List.size(); i++)
		v[i] = *__Arg_List[i];
	return __Input_Function(v);
}

bool Input_Handler::Change_Input_Function(double(*input_foo)(std::vector<Sint32>))
{
	if(!input_foo)
	{
		std::cout << "MSG Input_Handler::Change_Input_Function : No input foo supplied; if only arg list intended, use Input_Handler::Change_Arg_List\n";
	}
	else __Input_Function = input_foo;
	return true;
}

bool Input_Handler::Change_Arg_List(std::vector<Sint32> arg_list)
{
	if (!arg_list.size())
	{
		std::cerr << "ERR Input_Handler::Change_Arg_List : No arg list supplied\n";
		return false;
	}
	std::vector<std::shared_ptr<Sint32>> v(arg_list.size());
	for (unsigned i = 0; i < arg_list.size(); i++)
		v[i] = std::make_shared<Sint32>(arg_list[i]);
	__Arg_List = v;
	return true;
}

bool Input_Handler::Change_Dynamic_Arg_List(std::vector<Sint32*> arg_list)
{
	if (!arg_list.size())
	{
		std::cerr << "ERR Input_Handler::Change_Arg_List : No arg list supplied\n";
		return false;
	}
	std::vector<std::shared_ptr<Sint32>> v(arg_list.size());
	for (unsigned i = 0; i < arg_list.size(); i++)
	{
		if (!arg_list[i]) continue;
		v[i] = std::shared_ptr<Sint32>(arg_list[i], [](Sint32*) {});
	}
	__Arg_List = v;
	return true;
}

double(*Input_Handler::Get_Input_Function())(std::vector<Sint32>)
{
	if (!this) return nullptr;
	return *__Input_Function;
}

std::vector<std::shared_ptr<Sint32>> Input_Handler::Get_Arg_List()
{
	return __Arg_List;
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

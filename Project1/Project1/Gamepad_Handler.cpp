#include <iostream>
#include "Gamepad_Handler.h"
#include "System.h"

std::vector<std::shared_ptr<Gamepad_Handler>> Gamepad_Handler::__Gamepads;

Gamepad_Handler * Gamepad_Handler::Set(int gamepad_index)
{
	if (gamepad_index < 0 || gamepad_index >= SDL_NumJoysticks())
	{
		std::cerr << "ERR Gamepad_Handler::Set : No gamepad connected with given index (connected gamepads: " << SDL_NumJoysticks() << ", given index: " << gamepad_index + 1 << ")\n";
		return nullptr;
	}
	Gamepad_Handler::__Gamepads.emplace_back(std::make_shared<Gamepad_Handler>());
	Gamepad_Handler::__Gamepads.back().get()->__Joystick = SDL_JoystickOpen(gamepad_index);
	Gamepad_Handler::__Gamepads.back().get()->__Index = gamepad_index;
	return Gamepad_Handler::__Gamepads.back().get();
}

Gamepad_Handler * Gamepad_Handler::Get(int gamepad_index)
{
	if (gamepad_index < 0 || gamepad_index >= SDL_NumJoysticks())
	{
		//std::cerr << "ERR Gamepad_Handler::Set : No gamepad connected with given index (connected gamepads: " << SDL_NumJoysticks() << ", given index: " << gamepad_index + 1 << ")\n";
		return nullptr;
	}
	for (unsigned i = 0; i < __Gamepads.size(); i++)
	{
		if (__Gamepads[i]->__Index == gamepad_index) return __Gamepads[i].get();
	}
	//std::cerr << "ERR Gamepad_Handler::Get : No gamepad handler with given index\n";
	return nullptr;
}

unsigned Gamepad_Handler::Gamepad_Count()
{
	return __Gamepads.size();
}

double Gamepad_Handler::Get_Axis_State(int axis)
{
	if (!this)
	{
		std::cerr << "ERR Gamepad_Handler::Get_Axis_State : Gamepad not set (use Gamepad_Handler::Set function)\n";
		return 0.0;
	}

	if (!__Joystick)
	{
		std::cerr << "ERR Gamepad_Handler::Get_Axis_State : No gamepad supplied\n";
		return 0.0;
	}
	if (axis >= SDL_JoystickNumAxes(Get_Joystick()))
	{
		std::cout << "MSG Gamepad_Handler::Get_Axis_State : Given axis doesn't exist (no. axes: " << SDL_JoystickNumAxes(Get_Joystick()) << ")\n";
		return 0.0;
	}
	auto stt = SDL_JoystickGetAxis(__Joystick, axis);
	if (stt == 32767) return 1;
	return (double)stt / 32768.0;
}

Sint16 Gamepad_Handler::Get_Absolute_Axis_State(int axis)
{
	if (!this)
	{
		std::cerr << "ERR Gamepad_Handler::Get_Absolute_Axis_State : Gamepad not set (use Gamepad_Handler::Set function)\n";
		return 0;
	}
	if (!__Joystick)
	{
		std::cerr << "ERR Gamepad_Handler::Get_Absolute_Axis_State : No gamepad supplied\n";
		return 0;
	}
	if (axis >= SDL_JoystickNumAxes(Get_Joystick()))
	{
		std::cout << "MSG Gamepad_Handler::Get_Absolute_Axis_State : Given axis doesn't exist (no. axes: " << SDL_JoystickNumAxes(Get_Joystick()) << ")\n";
		return 0;
	}
	return SDL_JoystickGetAxis(__Joystick, axis);
}

bool Gamepad_Handler::Button_Down(Uint8 button)
{
	if (!this)
	{
		std::cerr << "ERR Gamepad_Handler::Button_Down : Gamepad not set (use Gamepad_Handler::Set function)\n";
		return false;
	}
	if (!__Joystick)
	{
		std::cerr << "ERR Gamepad_Handler::Button_Down : No gamepad supplied\n";
		return false;
	}
	for (std::map<Uint8, int>::iterator it = __Map.begin(); it != __Map.end(); it++)
		if (it->first == button && it->second == -2)
			return true;
	return false;
}

bool Gamepad_Handler::Button_Up(Uint8 button)
{
	if (!this)
	{
		std::cerr << "ERR Gamepad_Handler::Button_Up : Gamepad not set (use Gamepad_Handler::Set function)\n";
		return false;
	}
	if (!__Joystick)
	{
		std::cerr << "ERR Gamepad_Handler::Button_Up : No gamepad supplied\n";
		return false;
	}
	for (std::map<Uint8, int>::iterator it = __Map.begin(); it != __Map.end(); it++)
		if (it->first == button && it->second == -1)
			return true;
	return false;
}

bool Gamepad_Handler::Button_Held(Uint8 button, Uint32 time)
{
	if (!this)
	{
		std::cerr << "ERR Gamepad_Handler::Button_Held : Gamepad not set (use Gamepad_Handler::Set function)\n";
		return false;
	}
	if (!__Joystick)
	{
		std::cerr << "ERR Gamepad_Handler::Button_Held : No gamepad supplied\n";
		return false;
	}
	for (std::map<Uint8, int>::iterator it = __Map.begin(); it != __Map.end(); it++)
		if (it->first == button && it->second >= 0 && SDL_GetTicks() - it->second >= time)
			return true;
	return false;
}

bool Gamepad_Handler::Button_XHeld(Uint8 button, Uint32 time)
{
	if (!this)
	{
		std::cerr << "ERR Gamepad_Handler::Button_XHeld : Gamepad not set (use Gamepad_Handler::Set function)\n";
		return false;
	}
	if (!__Joystick)
	{
		std::cerr << "ERR Gamepad_Handler::Button_XHeld : No gamepad supplied\n";
		return false;
	}
	for (std::map<Uint8, int>::iterator it = __Map.begin(); it != __Map.end(); it++)
		if (it->first == button && it->second >= 0 && SDL_GetTicks() - it->second < time)
			return true;
	return false;
}

int Gamepad_Handler::Get_Index()
{
	return __Index;
}

SDL_Joystick * Gamepad_Handler::Get_Joystick()
{
	return __Joystick;
}

void Gamepad_Handler::__Events()
{
	for (unsigned i = 0; i < Gamepad_Count(); i++)
	{
		if (System::Events.type == SDL_JOYBUTTONDOWN)
			Gamepad_Handler::__Gamepads[i]->__Map.insert(std::make_pair(System::Events.jbutton.button, -2));
		if (System::Events.type == SDL_JOYBUTTONUP)
			for (std::map<Uint8, int>::iterator it = Gamepad_Handler::__Gamepads[i]->__Map.begin(); it != Gamepad_Handler::__Gamepads[i]->__Map.end(); it++)
				if (it->first == System::Events.jbutton.button)
					it->second = -1;
	}
}

void Gamepad_Handler::__Update()
{
	for (unsigned i = 0; i < Gamepad_Count(); i++)
	{
		for (std::map<Uint8, int>::iterator it = Gamepad_Handler::__Gamepads[i]->__Map.begin(); it != Gamepad_Handler::__Gamepads[i]->__Map.end();)
		{
			if (it->second == -1)
			{
				auto temp = it;
				++it;
				Gamepad_Handler::__Gamepads[i]->__Map.erase(temp);
			}
			else if (it->second == -2)
			{
				it->second = SDL_GetTicks();
				++it;
			}
			else ++it;
		}
	}
}

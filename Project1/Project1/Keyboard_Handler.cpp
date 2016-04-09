#include "Keyboard_Handler.h"
#include "System.h"
#include <iostream>

std::map<SDL_Keycode, int> Keyboard_Handler::__Map;

double Keyboard_Handler::Key_Down(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Keyboard_Handler::Key_Down : Key not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	Sint32 key = (Sint32)*it;

	for (std::map<SDL_Keycode, int>::iterator it = Keyboard_Handler::__Map.begin(); it != Keyboard_Handler::__Map.end(); it++)
		if (it->first == key && it->second == -2)
			return 1.0;
	return 0.0;
}

double Keyboard_Handler::Key_Up(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Keyboard_Handler::Key_Up : Key not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	Sint32 key = (Sint32)*it;

	for (std::map<SDL_Keycode, int>::iterator it = Keyboard_Handler::__Map.begin(); it != Keyboard_Handler::__Map.end(); it++)
		if (it->first == key && it->second == -1)
			return 1.0;
	return 0.0;
}

double Keyboard_Handler::Key_Held(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Keyboard_Handler::Key_Held : Key not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	Sint32 key = (Sint32)*it++;

	Sint32 time;
	if (it == args.end()) time = 0;
	else time = (Sint32)*it;

	for (std::map<SDL_Keycode, int>::iterator it = Keyboard_Handler::__Map.begin(); it != Keyboard_Handler::__Map.end(); it++)
		if (it->first == key && it->second >= 0 && SDL_GetTicks() - it->second >= (Uint32)time)
			return 1.0;
	return 0.0;
}



void Keyboard_Handler::__Events()
{
	if (System::Events.type == SDL_KEYDOWN)
		Keyboard_Handler::__Map.insert(std::make_pair(System::Events.key.keysym.sym, -2));
	if (System::Events.type == SDL_KEYUP)
		for (std::map<SDL_Keycode, int>::iterator it = Keyboard_Handler::__Map.begin(); it != Keyboard_Handler::__Map.end(); it++)
			if (it->first == System::Events.key.keysym.sym)
				it->second = -1;
}

void Keyboard_Handler::__Update()
{
	for (std::map<SDL_Keycode, int>::iterator it = Keyboard_Handler::__Map.begin(); it != Keyboard_Handler::__Map.end();)
	{
		if(it->second == -1)
		{
			auto temp = it;
			++it;
			Keyboard_Handler::__Map.erase(temp);
		}
		else if(it->second == -2)
		{
			it->second = SDL_GetTicks();
			++it;
		}
		else ++it;
	}
}

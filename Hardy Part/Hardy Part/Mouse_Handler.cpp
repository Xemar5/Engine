#include "Mouse_Handler.h"
#include <iostream>
#include "System.h"

std::map<Sint32, int> Mouse_Handler::__Map;

double Mouse_Handler::Button_Down(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Keyboard_Handler::Key_Down : Key not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	Sint32 key = (Sint32)*it;
	for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end(); it++)
		if (it->first == key && it->second == -2)
			return 1.0;
	return 0.0;
}

double Mouse_Handler::Button_Up(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Keyboard_Handler::Key_Up : Key not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	Sint32 key = (Sint32)*it;

	for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end(); it++)
		if (it->first == key && it->second == -1)
			return 1.0;
	return 0.0;
}

double Mouse_Handler::Button_Held(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Keyboard_Handler::Key_Held : Key not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	Sint32 key = (Sint32)*it++;

	Sint32 time;
	if (it == args.end()) time = 0;
	else time = (Sint32)*it;

	for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end(); it++)
		if (it->first == key && it->second >= 0 && SDL_GetTicks() - it->second >= (Uint32)time)
			return 1.0;
	return 0.0;
}



void Mouse_Handler::__Events()
{
	if (System::Events.type == SDL_MOUSEBUTTONDOWN)
		Mouse_Handler::__Map.insert(std::make_pair(System::Events.button.button, -2));
	if (System::Events.type == SDL_MOUSEBUTTONUP)
		for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end(); it++)
			if (it->first == System::Events.button.button)
				it->second = -1;
}

void Mouse_Handler::__Update()
{
	for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end();)
	{
		if (it->second == -1)
		{
			auto temp = it;
			++it;
			Mouse_Handler::__Map.erase(temp);
		}
		else if (it->second == -2)
		{
			it->second = SDL_GetTicks();
			++it;
		}
		else ++it;
	}
}

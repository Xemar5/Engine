#include "Input_Handler.h"
#include "System.h"

std::map<SDL_Keycode, int> Input_Handler::__Key_Map;

bool Input_Handler::Key_Down(SDL_Keycode key)
{
	for (std::map<SDL_Keycode, int>::iterator it = Input_Handler::__Key_Map.begin(); it != Input_Handler::__Key_Map.end(); it++)
		if (it->first == key && it->second == -2)
			return true;
	return false;
}

bool Input_Handler::Key_Up(SDL_Keycode key)
{
	for (std::map<SDL_Keycode, int>::iterator it = Input_Handler::__Key_Map.begin(); it != Input_Handler::__Key_Map.end(); it++)
		if (it->first == key && it->second == -1)
			return true;
	return false;
}

bool Input_Handler::Key_Held(SDL_Keycode key, Uint32 time)
{
	for (std::map<SDL_Keycode, int>::iterator it = Input_Handler::__Key_Map.begin(); it != Input_Handler::__Key_Map.end(); it++)
		if (it->first == key && it->second >= 0 && SDL_GetTicks() - it->second >= time)
			return true;
	return false;
}

void Input_Handler::__Input_Events()
{
	if (System::Events.type == SDL_KEYDOWN)
		__Key_Map.insert(std::make_pair(System::Events.key.keysym.sym, -2));
	if (System::Events.type == SDL_KEYUP)
		for (std::map<SDL_Keycode, int>::iterator it = Input_Handler::__Key_Map.begin(); it != Input_Handler::__Key_Map.end(); it++)
			if (it->first == System::Events.key.keysym.sym)
				it->second = -1;
}

void Input_Handler::__Input_Update()
{
	for (std::map<SDL_Keycode, int>::iterator it = Input_Handler::__Key_Map.begin(); it != Input_Handler::__Key_Map.end();)
	{
		if(it->second == -1)
		{
			auto temp = it;
			++it;
			__Key_Map.erase(temp);
		}
		else if(it->second == -2)
		{
			it->second = SDL_GetTicks();
			++it;
		}
		else ++it;
	}
}

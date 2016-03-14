#include "Keyboard_Handler.h"
#include "System.h"

std::map<SDL_Keycode, int> Keyboard_Handler::__Map;

bool Keyboard_Handler::Key_Down(SDL_Keycode key)
{
	for (std::map<SDL_Keycode, int>::iterator it = Keyboard_Handler::__Map.begin(); it != Keyboard_Handler::__Map.end(); it++)
		if (it->first == key && it->second == -2)
			return true;
	return false;
}

bool Keyboard_Handler::Key_Up(SDL_Keycode key)
{
	for (std::map<SDL_Keycode, int>::iterator it = Keyboard_Handler::__Map.begin(); it != Keyboard_Handler::__Map.end(); it++)
		if (it->first == key && it->second == -1)
			return true;
	return false;
}

bool Keyboard_Handler::Key_Held(SDL_Keycode key, Uint32 time)
{
	for (std::map<SDL_Keycode, int>::iterator it = Keyboard_Handler::__Map.begin(); it != Keyboard_Handler::__Map.end(); it++)
		if (it->first == key && it->second >= 0 && SDL_GetTicks() - it->second >= time)
			return true;
	return false;
}

bool Keyboard_Handler::Key_XHeld(SDL_Keycode key, Uint32 time)
{
	for (std::map<SDL_Keycode, int>::iterator it = Keyboard_Handler::__Map.begin(); it != Keyboard_Handler::__Map.end(); it++)
		if (it->first == key && it->second >= 0 && SDL_GetTicks() - it->second < time)
			return true;
	return false;
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

#pragma once
#include <SDL.h>
#include <map>
#include <iostream>
#include <vector>
#include <memory>
#include <initializer_list>


class Input_Handler
{
public:
	//*** Returns true if supplied button is being pushed
	static bool Key_Down(SDL_Keycode key);
	//*** Returns true if supplied button is being released
	static bool Key_Up(SDL_Keycode key);
	//*** Returns true if supplied button is being held for the given ammount of time in milisecounds
	static bool Key_Held(SDL_Keycode key, Uint32 time = 0);
private:
	//*** Updates every event, cares for key pushes and releases
	static void __Input_Events();
	//*** Updates timers on keys being pushed
	static void __Input_Update();
	//*** Contains every pushed key and the time it's being pushed for
	static std::map<SDL_Keycode, int> __Key_Map;

	friend class System;
};
#pragma once
#include <SDL.h>
#include <map>
#include <iostream>
#include <vector>
#include <memory>
#include <initializer_list>


class Keyboard_Handler
{
public:
	//*** Returns true if supplied key is being pushed
	//*** - (1st arg) key - the keyboard key to check
	static double Key_Down(std::initializer_list<Sint32> args);
	//*** Returns true if supplied key is being released
	//*** - (1st arg) key - the keyboard key to check
	static double Key_Up(std::initializer_list<Sint32> args);
	//*** Returns true if supplied key is being held for the given ammount of time in milisecounds
	//*** - (1st arg) key - the keyboard key to check
	//*** - (2nd arg) time - the time in which the condition is check; true if time passes
	static double Key_Held(std::initializer_list<Sint32> args);
private:
	//*** Updates every event, cares for key pushes and releases
	static void __Events();
	//*** Updates timers on keys being pushed
	static void __Update();
	//*** Contains every pushed key and the time it's being pushed for
	static std::map<SDL_Keycode, int> __Map;

	friend class Input_Handler;
};
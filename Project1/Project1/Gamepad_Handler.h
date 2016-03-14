#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>

class Gamepad_Handler
{
public:
	//*** Creates the gamepad handler class
	//*** - gamepad_index - the index of a gamepad
	static Gamepad_Handler* Set(int gamepad_index);
	//*** Returns the Gamepad_Handler of a given index if it exists
	static Gamepad_Handler* Get(int gamepad_index);
	//*** Returns the number of connected gamepads
	static unsigned Gamepad_Count();
	//*** Returns the state of given axis in range from -1 to 1
	double Get_Axis_State(int axis);
	//*** Returns the state of given axis in range from -32768 to 32767
	Sint16 Get_Absolute_Axis_State(int axis);
	//*** Returns true if supplied button is being pushed
	bool Button_Down(Uint8 button);
	//*** Returns true if supplied button is being released
	bool Button_Up(Uint8 button);
	//*** Returns true if supplied button is being held for the given ammount of time in milisecounds
	bool Button_Held(Uint8 button, Uint32 time = 0);
	//*** Reverse Button_Held function
	bool Button_XHeld(Uint8 button, Uint32 time);
	//*** Returns the index of this gamepad
	int Get_Index();
	//*** Return the SDL_GameController this Gamepad_Handler points to
	SDL_Joystick* Get_Joystick();
private:
	//*** This gamepad index
	int __Index = -1;
	//*** The Joystick this Handler points to
	SDL_Joystick* __Joystick = nullptr;
	////*** The GameController this Handler points to
	//SDL_GameController* __Gamepad = nullptr;
	//*** Updates every event, cares for button pushes and releases
	static void __Events();
	//*** Updates timers on buttons being pushed
	static void __Update();
	//*** Contains every pushed button and the time it's being pushed for
	std::map<Uint8, int> __Map;
	//*** Contains every connected gamepad
	static std::vector<std::shared_ptr<Gamepad_Handler>> __Gamepads;

	friend class Input_Handler;
};
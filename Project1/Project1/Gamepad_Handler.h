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

	//*** Returns the state of given axis in range from -1.0 to 1.0
	//*** - (1st arg) axis - the number of axis to check
	//*** - (2nd arg) gamepad - the index of gamepad with given axis
	static double Get_Axis_State(std::initializer_list<Sint32> args);
	//*** Returns the state of given axis if its value is positive (range from 0.0 to 1.0)
	//*** - (1st arg) axis - the number of axis to check
	//*** - (2nd arg) gamepad - the index of gamepad with given axis
	static double Get_Axis_State_Positive(std::initializer_list<Sint32> args);
	//*** Returns the state of given axis if its value is negative (range from 0.0 to 1.0)
	//*** - (1st arg) axis - the number of axis to check
	//*** - (2nd arg) gamepad - the index of gamepad with given axis
	static double Get_Axis_State_Negative(std::initializer_list<Sint32> args);

	//*** Returns the state of given axis in range from -32768 to 32767
	//*** - (1st arg) axis - the number of axis to check
	//*** - (2nd arg) gamepad - the index of gamepad with given axis
	static double Get_Absolute_Axis_State(std::initializer_list<Sint32> args);
	//*** Returns the state of given axis if its value is positive (range from 0 to 32767)
	//*** - (1st arg) axis - the number of axis to check
	//*** - (2nd arg) gamepad - the index of gamepad with given axis
	static double Get_Absolute_Axis_State_Positive(std::initializer_list<Sint32> args);
	//*** Returns the state of given axis if its value is negative (range from 0 to 32767)
	//*** - (1st arg) axis - the number of axis to check
	//*** - (2nd arg) gamepad - the index of gamepad with given axis
	static double Get_Absolute_Axis_State_Negative(std::initializer_list<Sint32> args);

	//*** Returns true if supplied button is being pushed
	//*** - (1st arg) button - the index of button to check
	//*** - (2nd arg) gamepad - the index of gamepad with given button
	static double Button_Down(std::initializer_list<Sint32> args);
	//*** Returns true if supplied button is being released
	//*** - (1st arg) button - the index of button to check
	//*** - (2nd arg) gamepad - the index of gamepad with given button
	static double Button_Up(std::initializer_list<Sint32> args);
	//*** Returns true if supplied button is being held for the given ammount of time in milisecounds
	//*** - (1st arg) button - the index of button to check
	//*** - (2nd arg) gamepad - the index of gamepad with given button
	//*** - (3rd arg) time - the time in which the condition is check; true if time passes
	static double Button_Held(std::initializer_list<Sint32> args);

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
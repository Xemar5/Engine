#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>

class Gamepad_Handler : public Controller
{
public:
	//*** Creates the gamepad handler class
	//*** - gamepad_index - the index of a gamepad
	static Gamepad_Handler* Set(int gamepad_index);
	//*** Creates the gamepad handler class
	//*** - gamepad_index - the index of a gamepad
	bool Remove();
	//*** Returns the Gamepad_Handler of a given index if it exists
	static Gamepad_Handler* Get(int gamepad_index);
	//*** Returns the number of connected gamepads
	static unsigned Gamepad_Count();

	//*** Returns the state of given axis in range from -1.0 to 1.0
	//*** - (1st arg) gamepad - the index of gamepad with given axis
	//*** - (2nd arg) axis - the number of axis to check
	static double Get_Axis_State(std::vector<Sint32> args);
	//*** Returns the state of given axis if its value is positive (range from 0.0 to 1.0)
	//*** - (1st arg) gamepad - the index of gamepad with given axis
	//*** - (2nd arg) axis - the number of axis to check
	static double Get_Axis_State_Positive(std::vector<Sint32> args);
	//*** Returns the state of given axis if its value is negative (range from 0.0 to 1.0)
	//*** - (1st arg) gamepad - the index of gamepad with given axis
	//*** - (2nd arg) axis - the number of axis to check
	static double Get_Axis_State_Negative(std::vector<Sint32> args);

	//*** Returns the state of given axis in range from -32768 to 32767
	//*** - (1st arg) gamepad - the index of gamepad with given axis
	//*** - (2nd arg) axis - the number of axis to check
	static double Get_Absolute_Axis_State(std::vector<Sint32> args);
	//*** Returns the state of given axis if its value is positive (range from 0 to 32767)
	//*** - (1st arg) gamepad - the index of gamepad with given axis
	//*** - (2nd arg) axis - the number of axis to check
	static double Get_Absolute_Axis_State_Positive(std::vector<Sint32> args);
	//*** Returns the state of given axis if its value is negative (range from 0 to 32767)
	//*** - (1st arg) gamepad - the index of gamepad with given axis
	//*** - (2nd arg) axis - the number of axis to check
	static double Get_Absolute_Axis_State_Negative(std::vector<Sint32> args);

	//*** Returns true if supplied button is being pushed
	//*** - (1st arg) gamepad - the index of gamepad with given button
	//*** - (2nd arg) button - the index of button to check
	static double Button_Down(std::vector<Sint32> args);
	//*** Returns true if supplied button is being released
	//*** - (1st arg) gamepad - the index of gamepad with given button
	//*** - (2nd arg) button - the index of button to check
	static double Button_Up(std::vector<Sint32> args);
	//*** Returns true if supplied button is being held for the given ammount of time in milisecounds
	//*** - (1st arg) gamepad - the index of gamepad with given button
	//*** - (2nd arg) button - the index of button to check
	//*** - (3rd arg) time - the time in which the condition is check; true if time passes
	static double Button_Held(std::vector<Sint32> args);

	//*** Returns true if supplied button is being pushed
	//*** - (1st arg) gamepad - the index of gamepad with given button
	//*** - (2nd arg) hat direction - the index of button to check
	static double Hat_Down(std::vector<Sint32> args);
	//*** Returns true if supplied button is being released
	//*** - (1st arg) gamepad - the index of gamepad with given button
	//*** - (2nd arg) hat direction - the index of button to check
	static double Hat_Up(std::vector<Sint32> args);
	//*** Returns true if supplied button is being held for the given ammount of time in milisecounds
	//*** - (1st arg) gamepad - the index of gamepad with given button
	//*** - (2nd arg) hat direction - the index of button to check
	//*** - (3rd arg) time - the time in which the condition is check; true if time passes
	static double Hat_Held(std::vector<Sint32> args);


	//*** Returns the index of this gamepad
	int Get_SDL_Index();
	//*** Return the SDL_GameController this Gamepad_Handler points to
	SDL_Joystick* Get_Joystick();

	//*** Returns the container of all initialized gamepads
	static std::vector<std::shared_ptr<Gamepad_Handler>> Get_Gamepads();

private:
	////*** This gamepad index
	//int __Index = -1;
	//*** The Joystick this Handler points to
	SDL_Joystick* __Joystick = nullptr;
	//*** Updates every event, cares for button pushes and releases
	static void __Events();
	//*** Updates timers on buttons being pushed
	static void __Update();
	//*** Contains every connected gamepad
	static std::vector<std::shared_ptr<Gamepad_Handler>> __Gamepads;

	friend class Input_Handler;
};
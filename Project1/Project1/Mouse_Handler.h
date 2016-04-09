#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>


class Mouse_Handler
{
public:
	//*** Returns true if supplied button is being pushed
	//*** - (1st arg) button - the mouse button to check
	static double Button_Down(std::vector<Sint32> args);
	//*** Returns true if supplied button is being released
	//*** - (1st arg) button - the mouse button to check
	static double Button_Up(std::vector<Sint32> args);
	//*** Returns true if supplied button is being held for the given ammount of time in milisecounds
	//*** - (1st arg) button - the mouse button to check
	//*** - (2nd arg) time - the time in which the condition is check; true if time passes
	static double Button_Held(std::vector<Sint32> args);

	//*** Returns the state of given axis in range from -1.0 to 1.0
	//*** - (1st arg) axis - the number of axis to check
	//*** - (2nd arg) gamepad - the index of gamepad with given axis
	static double Get_Relative_Mouse_State(std::vector<Sint32> args);
private:
	//*** Updates every event, cares for button pushes and releases
	static void __Events();
	//*** Updates timers on button being pushed
	static void __Update();
	//*** Contains every pushed button and the time it's being pushed for
	static std::map<Sint32, int> __Map;

	friend class Input_Handler;
};
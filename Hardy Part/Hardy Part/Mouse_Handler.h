#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>

class Entity;

class Mouse_Handler
{
public:
	//*** Returns 1 if supplied button is being pushed; otherwise returns 0
	//*** - (1st arg) button - the mouse button to check
	static double Button_Down(std::vector<Sint32> args);
	//*** Returns 1 if supplied button is being released; otherwise returns 0
	//*** - (1st arg) button - the mouse button to check
	static double Button_Up(std::vector<Sint32> args);
	//*** Returns true if supplied button is being held for the given ammount of time in miliseconds
	//*** - (1st arg) button - the mouse button to check
	//*** - (2nd arg) time - the time in which the condition is check;
	//*** returns 1 if time passes; otherwise returns 0
	static double Button_Held(std::vector<Sint32> args);

	//*** Returns the mouse pos based on the Screen::__Scale
	static std::pair<int, int> Get_Mouse_Pos();

	//*** Returns the X position of the mouse in range from -1.0 to 1.0
	//*** - (1st arg) X foothoold - the X coordinate of the foothold
	//*** - (2nd arg) Y foothoold - the Y coordinate of the foothold
	static double Get_Relative_Mouse_X_State(std::vector<Sint32> args);
	//*** Returns the Y position of the mouse in range from -1.0 to 1.0
	//*** - (1st arg) X foothoold - the X coordinate of the foothold
	//*** - (2nd arg) Y foothoold - the Y coordinate of the foothold
	static double Get_Relative_Mouse_Y_State(std::vector<Sint32> args);

	//*** Returns true if mouse is within the supplied entity
	static bool Contains_Mouse(Entity* ent);

private:
	//*** Updates every event, cares for button pushes and releases
	static void __Events();
	//*** Updates timers on button being pushed
	static void __Update();
	//*** Contains every pushed button and the time it's being pushed for
	static std::map<Sint32, int> __Map;

	friend class Input_Handler;
};
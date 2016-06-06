#pragma once
#include <map>
#include <vector>
#include <memory>
#include <SDL.h>
#include "Input.h"
#include "System.h"
#include "Mapping.h"

#define KEYBOARD -1

class Device
{
public:
	//*** Initializes the Device handler
	static void Init(std::string path);
	//*** The cleanup for the events function
	//*** Gets rids of unused inputs
	static void Events_CleanUp();
	//*** Handles mouse/keyboard/gamepad inputs
	static void Events();
	//*** Returns the device with given index
	//*** if -1, returns keyboard (use KEYBOARD)
	//*** if >=0, returns the gamepad with given index if it exists
	static Device& Get(Sint32 index = -1);
	//*** Returns a device that is being used
	static Sint32 Which();
	//*** Returns the map of all inputs this device currently uses
	size_t Map_Size() { return _Inputs.size(); };
	//*** The keybindings for this device
	Mapping Bindings;
	//*** Returns true if given action name is in the binding map
	bool Has_Action(std::string name) { return Bindings.Has_Binding(name); };

	virtual Input& operator[](const char* name);
	virtual Input& operator[](Input input);
	Device()
	{
		_Inputs = { Input::Set(IT_UNDEFINED, IK_UNDEFINED) };
		Bindings << "UNDEFINED" + _Inputs[0];
	};
protected:
	//*** The container of all inputs this class currently uses
	std::vector<Input> _Inputs;
};




enum Mouse_Input
{
	MI_AXIS,
	MI_BUTTON
};
enum Mouse_Axis
{
	MA_X,
	MA_Y
};

class Keyboard : public Device
{
public:
	//*** The cleanup for the events function
	//*** Gets rids of unused inputs
	void Events_CleanUp();
	//*** Handles mouse/keyboard inputs
	void Events();
	//*** The global Keyboard/Mouse object
	static Keyboard Get;
	//*** Returns true if given entity contains mouse cursor
	static bool Contains_Mouse(Entity* ent);
private:
	Keyboard()
	{
		_Inputs.push_back(Input::Set(IT_MOUSE_AXIS, MA_X));
		_Inputs.push_back(Input::Set(IT_MOUSE_AXIS, MA_Y));
	};

};
typedef Keyboard Mouse;



enum Gamepad_Input
{
	GI_UNDEFINED,
	GI_BUTTON,
	GI_AXIS,
	GI_HAT
};
enum DPad_Input
{
	DP_UP,
	DP_LEFT,
	DP_DOWN,
	DP_RIGHT
};

class Gamepad : public Device
{
public:
	//*** Initializes a new gamepad
	static bool Set(Sint32 index);
	//*** Returns the addres of a gamepad with given id
	static Gamepad& Get(Sint32 index);
	//*** The deadzone for all axes and gamepads
	//*** Axes wont trigger if the value not greater than the Deadzone
	static Sint32 Deadzone;

	//*** The cleanup for the events function
	//*** Gets rids of unused inputs
	void Events_CleanUp();
	//*** Handles gamepad inputs
	void Events();
	//*** Removes this gamepad from the list of all initialized gamepads
	bool Remove();
private:
	//*** The pointer to the sdl Joystick
	SDL_Joystick* Joystick = nullptr;
	//*** The container of all initialized gamepads
	static std::vector<std::unique_ptr<Gamepad>> __Gamepads;
	Gamepad(){}

	friend class Device;
};
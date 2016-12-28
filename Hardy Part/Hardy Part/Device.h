#pragma once
#include <map>
#include <vector>
#include <memory>
#include <SDL.h>
#include "Input.h"
#include "System.h"
#include "Mapping.h"
#include "Entity.h"

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
	//*** Returns the device with given name
	static Device& Get(std::string name);
	//*** Returns a device that is being used
	static Sint32 Which();
	//*** Returns the vector of all Devices
	static std::vector<Device*> All();
	//*** Returns the current device that is being used
	static Device& GetCurrent() { return Device::Get(Device::Which()); }

	//*** Returns the current input
	static Input* CurrentInput() { return _CurrentInput; }
	//*** Returns the name of this Device
	std::string Name() { return _Name; }
	//*** Returns the map of all inputs this device currently uses
	size_t Map_Size() { return _Inputs.size(); };
	//*** The keybindings for this device
	Mapping Bindings;
	//*** Returns true if given action name is in the binding map
	bool Has_Action(std::string name) { return Bindings.Has_Binding(name); };

	//*** Removes all incoming inputs
	void ClearInputs();
	//*** Removes all incoming inputs from all connected devices
	static void ClearAllDeviceInput();

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
	//*** The current input;
	static Input* _CurrentInput;
	//*** The name of this device
	std::string _Name;
};




class Keyboard : public Device
{
public:
	//*** The cleanup for the events function
	//*** Gets rids of unused inputs
	void Events_CleanUp();
	//*** Handles mouse/keyboard inputs
	void Events();
	//*** Handles mouse update
	void Update();
	//*** The global Keyboard/Mouse object
	static Keyboard Get;
	//*** Returns true if given entity contains mouse cursor
	static bool Contains_Mouse(Entity<> ent);
	//*** The time after which mouse is considered idle
	static double MouseIdleTime;
private:
	Keyboard()
	{
		_Name = "Keyboard";
		//_Inputs.push_back(Input::Change(IT_MOUSE_AXIS, MA_X, -1, -1, IS_MOVING));
		//_Inputs.push_back(Input::Change(IT_MOUSE_AXIS, MA_Y, -1, -1, IS_MOVING));
	};

};
typedef Keyboard Mouse;



//enum Gamepad_Input
//{
//	GI_UNDEFINED,
//	GI_BUTTON,
//	GI_AXIS,
//	GI_AXIS_INV,
//	GI_AXIS_HALV,
//	GI_AXIS_INV_HALV,
//	GI_HAT
//};
//enum DPad_Input
//{
//	DP_UP,
//	DP_LEFT,
//	DP_DOWN,
//	DP_RIGHT
//};

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


	Sint32 SDL_InstanceID() { return SDL_JoystickInstanceID(Joystick); }
	//*** The cleanup for the events function
	//*** Gets rids of unused inputs
	void Events_CleanUp();
	//*** Handles gamepad inputs
	void Events();
	//*** Removes this gamepad from the list of all initialized gamepads
	static bool Remove(Sint32 index);
private:
	//*** The index of this joystick used in SDL_JOYDEVICEADDED / REMOVED
	Sint32 __OpenedIndex = 0;
	//*** Resolves Gamepad axis events
	void Handle_Axis();
	//*** Resolves Gamepad hat events
	void Handle_Hat();

	//*** The pointer to the sdl Joystick
	SDL_Joystick* Joystick = nullptr;
	//*** The container of all initialized gamepads
	static std::vector<std::unique_ptr<Gamepad>> __Gamepads;
	Gamepad(){}

	friend class Device;
};
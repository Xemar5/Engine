#pragma once
#include <memory>
#include <vector>
#include <SDL.h>
#include <map>
#include <iostream>
#include <fstream>


class Input_Handler;
typedef std::map<std::string, std::shared_ptr<Input_Handler>> Input_Preset;

class Input_Handler
{
public:
	//*** Creates and initializes the Input Handler object
	//*** Use when arguments aren't changing over time; use Set_Dynamic otherwise
	//*** - input_foo - the function this class calls to check if an imput has occured
	//*** - arg_list - the list of passive arguments for the input_foo to call with
	//*** Returns the shared pointer to a newly created object
	static std::shared_ptr<Input_Handler> Set(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32> arg_list);
	//*** Loads the Input Handler from given stream
	//*** - is - input stream key presets are ging to be load from
	//*** - controller_name - the name of the preset to load ( in [ ] brackets )
	//*** - controller_index - the index of gamepad ( leave blank or -1 if keyboard/mouse )
	static Input_Preset Load(std::istream& is, std::string controller_name, int controller_index = -1);
	//*** Calls the __Input_Function function with __Arg_List
	double Check();


	//*** The function this Input Handler checks for an imput evens
	double(*Input_Function)(std::vector<Sint32>) = nullptr;
	//*** The list of arguments to call the __Input_Function function
	std::vector<Sint32> Input_Args;
	//*** The default empty preset of all essential keybinds (mainly gamepads)
	static Input_Preset Empty_Preset;

private:


	//*** Updates the Keyboard Handler and Gamepad Handler
	static void __Update();
	//*** Handles events in Keyboard Handler and Gamepad Handler
	static void __Events();

	//*** Decodes the string and returns Input Args
	//*** Used in Input_Handler::Load
	//*** - str - the string to decode
	//*** - controller_index - the index of controller ( leave blank or -1 if keyboard/mouse )
	static std::shared_ptr<Input_Handler> __Decode_Load(std::string str, int controller_index);

	friend class System;
};


#include "Mouse_Handler.h"
#include "Keyboard_Handler.h"
#include "Gamepad_Handler.h"

#pragma once
#include "Input_Handler.h"
#include <iostream>


class Input_Preset
{
public:

	//*** Creates new Input_Preset and returns pointer to it
	//*** Adds the Preset to __Input_Presets list (obtainable from Get_Input_Presets)
	//*** - gamepad_index - the index of gamepad the preset is being set for; does nothing for keyboard
	static Input_Preset* Set_Gamepad(int gamepad_index = -1);

	//*** Creates new Input_Preset and returns pointer to it
	//*** Adds the Preset to __Input_Presets list (obtainable from Get_Input_Presets)
	//*** - gamepad_index - the index of gamepad the preset is being set for; does nothing for keyboard
	static Input_Preset* Set_Keyboard();

	//*** Creates new Input_Preset and returns pointer to it
	//*** Adds the Preset to __Input_Presets list (obtainable from Get_Input_Presets)
	//*** - gamepad_index - the index of gamepad the preset is being set for; does nothing for keyboard
	static Input_Preset* Load_Form_File();

	//*** The up input function
	Input_Function Up = nullptr;
	//*** The down input function
	Input_Function Down = nullptr;
	//*** The left input function
	Input_Function Left = nullptr;
	//*** The right input function
	Input_Function Right = nullptr;

	//*** The alternative up input function ( only for gamepads )
	Input_Function UpAlt = nullptr;
	//*** The alternative down input function ( only for gamepads )
	Input_Function DownAlt = nullptr;
	//*** The alternative left input function ( only for gamepads )
	Input_Function LeftAlt = nullptr;
	//*** The alternative right input function ( only for gamepads )
	Input_Function RightAlt = nullptr;
	

	//*** The aim vertical input function ( up to down )
	Input_Function Aim_V = nullptr;
	//*** The aim horizontal input function ( left to right ) 
	Input_Function Aim_H = nullptr;

	//*** The action input function ( square for ps3 )
	Input_Function Action = nullptr;
	//*** The cancel input function ( circle for ps3 )
	Input_Function Cancel = nullptr;
	//*** The switch input function ( triangle for ps3 )
	Input_Function Switch = nullptr;
	//*** The accept input function ( cross for ps3 )
	Input_Function Accept = nullptr;

	//*** The L1 input function
	Input_Function L1 = nullptr;
	//*** The L2 input function
	Input_Function L2 = nullptr;
	//*** The R1 input function
	Input_Function R1 = nullptr;
	//*** The R2 input function
	Input_Function R2 = nullptr;

	//*** The start input function ( start for ps3 )
	Input_Function Start = nullptr;
	//*** The select input function ( select for ps3 )
	Input_Function Select = nullptr;


	Input_Preset& operator<<(Input_Function arg);
	Input_Preset& operator=(Input_Preset& const arg);

	//*** Returns the container of all initialized input preset
	static std::vector<std::shared_ptr<Input_Preset>> Get_Input_Presets();

private:
	//*** The container of all initialized input presets
	static std::vector<std::shared_ptr<Input_Preset>> __Input_Presets;
};
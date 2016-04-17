#pragma once
#include <memory>
#include <vector>
#include <SDL.h>

class Input_Handler
{
public:
	//*** Creates and initializes the Input Handler object
	//*** - input_foo - the function this class calls to check if an imput has occured
	//*** - arg_list - the list of arguments for the input_foo to call with
	//*** Returns the shared pointer to a newly created object
	static std::shared_ptr<Input_Handler> Set(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32> arg_list);
	//*** Calls the __Input_Function function with __Arg_List
	double Check();
	//*** Changes the __Input_Function of this Input Handler object
	//*** The arg_list can be left default initialized so no changes will be made
	bool Change_Input_Function(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32> arg_list = {});
	//*** Changes the __Arg_List of this Input Handler object
	bool Change_Arg_List(std::vector<Sint32> arg_list);

private:
	//*** The function this Input Handler checks for an imput evens
	double(*__Input_Function)(std::vector<Sint32>) = nullptr;
	//*** The list of arguments to call the __Input_Function function
	std::vector<Sint32> __Arg_List;


	//*** Updates the Keyboard Handler and Gamepad Handler
	static void __Update();
	//*** Handles events in Keyboard Handler and Gamepad Handler
	static void __Events();

	friend class System;
};
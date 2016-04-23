#pragma once
#include <memory>
#include <vector>
#include <SDL.h>

class Input_Handler;
typedef std::shared_ptr<Input_Handler> Input_Function;

class Input_Handler
{
public:
	//*** Creates and initializes the Input Handler object
	//*** Use when arguments aren't changing over time; use Set_Dynamic otherwise
	//*** - input_foo - the function this class calls to check if an imput has occured
	//*** - arg_list - the list of passive arguments for the input_foo to call with
	//*** Returns the shared pointer to a newly created object
	static std::shared_ptr<Input_Handler> Set(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32> arg_list);
	//*** Creates and initializes the Input Handler object
	//*** Use when arguments are changing over time; use Set otherwise
	//*** - input_foo - the function this class calls to check if an imput has occured
	//*** - arg_list - the list of dynamic arguments for the input_foo to call with
	//*** Returns the shared pointer to a newly created object
	static std::shared_ptr<Input_Handler> Set_Dynamic(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32*> arg_list);
	//*** Calls the __Input_Function function with __Arg_List
	double Check();
	//*** Changes the __Input_Function of this Input Handler object
	//*** The arg_list can be left default initialized so no changes will be made
	bool Change_Input_Function(double(*input_foo)(std::vector<Sint32>));
	//*** Changes the __Arg_List of this Input Handler object
	bool Change_Arg_List(std::vector<Sint32> arg_list);
	//*** Changes the __Arg_List of this Input Handler object
	bool Change_Dynamic_Arg_List(std::vector<Sint32*> arg_list);

	//*** Returns the Input Function of this Input Handler
	double(*Get_Input_Function())(std::vector<Sint32>);
	//*** Returns the Arg List of this Input Handler
	std::vector<std::shared_ptr<Sint32>> Get_Arg_List();

private:
	//*** The function this Input Handler checks for an imput evens
	double(*__Input_Function)(std::vector<Sint32>) = nullptr;
	//*** The list of arguments to call the __Input_Function function
	std::vector<std::shared_ptr<Sint32>> __Arg_List;


	//*** Updates the Keyboard Handler and Gamepad Handler
	static void __Update();
	//*** Handles events in Keyboard Handler and Gamepad Handler
	static void __Events();

	friend class System;
};

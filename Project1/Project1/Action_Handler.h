#pragma once
#include <SDL.h>
#include <memory>

class Action_Input
{
	std::unique_ptr<SDL_Keycode> __Keycode = nullptr;
};

class Action_Handler
{
	Action_Input __Actions;
};
#include "Input_Handler.h"
#include "Keyboard_Handler.h"
#include "Gamepad_Handler.h"

void Input_Handler::__Update()
{
	Keyboard_Handler::__Update();
	Gamepad_Handler::__Update();
}

void Input_Handler::__Events()
{
	Keyboard_Handler::__Events();
	Gamepad_Handler::__Events();
}

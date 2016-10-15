#include "State2.h"
#include "Device.h"

void State2::Create()
{
	
}

void State2::Update()
{
}

void State2::Events()
{
	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE, IS_PUSHED)].Down())
		State::New<State1>();
	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_SPACE, IS_PUSHED)].Down())
		State::New<State1>(Get_Entities());
}

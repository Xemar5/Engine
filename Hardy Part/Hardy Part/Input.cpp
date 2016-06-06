#include <SDL.h>
#include "Input.h"
#include "Device.h"
#include <iostream>
#define PRNT(NAME) std::cout << #NAME << ":\t" << (NAME) << std::endl;

Input Input::Set(Sint32 type, Sint32 key, Input_State state/*, Sint32 gamepad*/)
{
	Input ip;
	ip.__Type = (Input_Type)type;
	ip.__Key = key;
	ip.State = state;
	return ip;
}


double Input::Down()
{
	if (!this) return 0.0;
	if (__Type == IT_UNDEFINED) return 0;
	else if (__Type == IT_MOUSE_AXIS)
	{
		Sint32 new_state = 0;
		if (__Key == MA_X) SDL_GetMouseState(&new_state, nullptr);
		if (__Key == MA_Y) SDL_GetMouseState(nullptr, &new_state);
		if ((Sint32)((double)new_state / Screen::Get_Scale()) / Screen::Get_Scale() != State)
		{
			State = (Sint32)((double)new_state / Screen::Get_Scale());
			return State;
		}
		return 0;
	}
	else if (this->State == IS_PUSHED) return 1;
	return 0;
}

double Input::Up()
{
	if (!this) return 0.0;
	if (__Type == IT_UNDEFINED) return 0;
	else if (__Type == IT_MOUSE_AXIS)
	{
		Sint32 new_state = 0;
		if (__Key == MA_X) SDL_GetMouseState(&new_state, nullptr);
		if (__Key == MA_Y) SDL_GetMouseState(nullptr, &new_state);
		if ((Sint32)((double)new_state / Screen::Get_Scale()) / Screen::Get_Scale() != State)
		{
			State = (Sint32)((double)new_state / Screen::Get_Scale());
			return State;
		}
		return 0;
	}
	else if (this->State == IS_RELEASED) return 1;
	return 0;
}

double Input::Held(Sint32 time)
{
	if (!this) return 0.0;
	if (__Type == IT_UNDEFINED) return 0;
	else if ((__Type & 0b111) == IT_GAMEPAD_AXIS && Input::Which_Controller(__Type) >= 0)
	{
		State = (Input_State)SDL_JoystickGetAxis(SDL_JoystickFromInstanceID(Which_Controller(__Type)), __Key);
		if (State == 32767) return 1;
		if (abs(State) < abs(Gamepad::Deadzone)) return 0.;
		return (State - (Gamepad::Deadzone * (State < 0 ? -1 : 1))) / (32768.0 - abs(Gamepad::Deadzone));
	}
	else if (__Type == IT_MOUSE_AXIS)
	{
		if (__Key == MA_X) SDL_GetMouseState(&State, nullptr);
		if (__Key == MA_Y) SDL_GetMouseState(nullptr, &State);
		return State = (Sint32)((double)State / Screen::Get_Scale());
	}
	else if (this->State >= 0) return (SDL_GetTicks() - this->State >= (unsigned)time ? SDL_GetTicks() - this->State : 0);
	return 0;
}

bool Input::operator==(const Input & dst) const
{
	Uint8 type1 = __Type & 0b111;
	Uint8 type2 = dst.__Type & 0b111;
	if (type1 == IT_UNDEFINED || type2 == IT_UNDEFINED) return false;
	if (__Key == IK_UNDEFINED || dst.__Key == IK_UNDEFINED) return false;
	if (State == IS_UNDEFINED || dst.State == IS_UNDEFINED) return false;

	if (type1 != IT_ANY		&& type2 != IT_ANY			&& type1 != type2) return false;
	if (__Key != IK_ANY		&& dst.__Key != IK_ANY		&& __Key != dst.__Key) return false;
	if (State != IS_ANY		&& dst.State != IS_ANY		&& State != dst.State) return false;
	return true;
}



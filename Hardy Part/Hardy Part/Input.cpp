#include <SDL.h>
#include "Input.h"
#include "Device.h"
#include <iostream>
#define PRNT(NAME) std::cout << #NAME << ":\t" << (NAME) << std::endl;

double Input::ClickTime = 400;

Input Input::Set(Sint32 type, Sint32 key, Sint32 controllerID, Sint32 variant, Input_State state)
{
	Input ip;
	ip.__Type = (Input_Type)type;
	ip.__Key = key;
	ip.__Variant = variant;
	ip.State = state;
	if (type == IT_KEYBOARD_KEY || type == IT_MOUSE_AXIS || type == IT_MOUSE_BUTTON)
		ip.__ControllerID = CI_KEYBOARD_MOUSE;
	else
		ip.__ControllerID = (Controller_Index) controllerID;
	return ip;
}


std::string Input::KeyName() const
{
	std::string mbutton = "";
	switch (__Type)
	{
	case IT_GAMEPAD_AXIS: return "Gamepad Axis " + std::to_string(__Key);
	case IT_GAMEPAD_HAT: return "Gamepad Hat " + (__Variant ? std::to_string(__Variant) : "") + std::to_string(__Key);
	case IT_GAMEPAD_BUTTON: return "Gamepad Button " + std::to_string(__Key);
	case IT_KEYBOARD_KEY: return "Keyboard Key " + std::string(SDL_GetKeyName(__Key));
	case IT_MOUSE_AXIS: return "Mouse " + (__Key == MA_X ? std::string("Horizontal") : std::string("Vertical"));
	case IT_MOUSE_BUTTON:
		if (__Key == SDL_BUTTON_LEFT) mbutton = "Left";
		else if(__Key == SDL_BUTTON_RIGHT) mbutton = "Right";
		else if (__Key == SDL_BUTTON_MIDDLE) mbutton = "Middle";
		else mbutton = std::to_string(__Key);
		return "Mouse Button " + mbutton;
	default: break;
	}
	return "[Unknown Input]";
}

Device & Input::Controller() const
{
	return Device::Get((Sint32)__ControllerID);
}
//
//double Input::__Handle_Mouse_Axis(Input* input)
//{
//	if (!input) { Output_Handler::Output << "MSG Input::_Handle_Mouse_Axis : No Input supplied\n"; return 0; }
//	//Sint32 new_value = 0;
//	if (input->Key() == MA_X) SDL_GetMouseState(&input->__Variant, nullptr);
//	if (input->Key() == MA_Y) SDL_GetMouseState(nullptr, &input->__Variant);
//	input->__Variant = (Sint32)((double)input->__Variant / Screen::Get_Scale());
//	std::cout << input->__Variant << " " << input->Value << "; ";
//	if (input->__Variant != input->Value)
//	{
//		//input->Value = (Sint32)((double)new_value / Screen::Get_Scale());
//		//return input->Value;
//		return 1;
//	}
//	return 0;
//}

double Input::Down()
{
	if (!this) return 0.0;
	else if (__Type == IT_UNDEFINED) return 0;
	//else if (__Type == IT_MOUSE_AXIS) return __Handle_Mouse_Axis(this);
	else if (this->State == IS_PUSHED) return 1;
	return 0;
}

double Input::Up()
{
	if (!this) return 0.0;
	else if (__Type == IT_UNDEFINED) return 0;
	//else if (__Type == IT_MOUSE_AXIS) return __Handle_Mouse_Axis(this);
	else if (this->State == IS_RELEASED) return 1;
	return 0;
}

double Input::Click()
{
	if (!this) return 0.0;
	else if (__Type == IT_UNDEFINED) return 0;
	//else if (__Type == IT_MOUSE_AXIS) return __Handle_Mouse_Axis(this);
	else if (this->State == IS_RELEASED && SDL_GetTicks() - this->__Time < ClickTime) return 1;
	return 0;
}

double Input::Held(Sint32 time)
{
	if (!this) return 0.0;
	else if (__Type == IT_UNDEFINED) return 0;
 	else if (__Type == IT_GAMEPAD_AXIS)
	{
		Value = SDL_JoystickGetAxis(SDL_JoystickFromInstanceID(__ControllerID), __Key);
		if (__Variant == IV_AXIS_INVERTED || __Variant == AT_AXIS_INVERTED_HALVED)
			Value = -Value - 1;
		if (Value == 32767) return 1;
		if (abs(Value) < abs(Gamepad::Deadzone)) return 0.;
		return (Value - (Gamepad::Deadzone * (Value < 0 ? -1 : 1))) / (32768.0 - abs(Gamepad::Deadzone));
	}
	else if (__Type == IT_MOUSE_AXIS)
	{
		if (__Key == MA_X) SDL_GetMouseState(&Value, nullptr);
		if (__Key == MA_Y) SDL_GetMouseState(nullptr, &Value);
		return Value = (Sint32)((double)Value / Screen::Get_Scale());
	}
	else if (State == IS_HELD)
	{
		Uint32 now = SDL_GetTicks();
		return (now - this->__Time >= (unsigned)time ? now - this->State : 0);
	}
	return 0;
}

bool Input::operator==(const Input & dst) const
{
	if (__Type == IT_UNDEFINED	|| dst.__Type == IT_UNDEFINED) return false;
	if (__Key == IK_UNDEFINED	|| dst.__Key == IK_UNDEFINED) return false;
	if (State == IS_UNDEFINED	|| dst.State == IS_UNDEFINED) return false;
	if (__ControllerID == -3	|| dst.__ControllerID == -3) return false;

	if ((__Type & dst.__Type) == 0) return false;
	if (__Key != IK_ANY				&& dst.__Key != IK_ANY			&& __Key != dst.__Key) return false;
	if (State != IS_ANY				&& dst.State != IS_ANY			&& State != dst.State) return false;
	if (__ControllerID != CI_ANY	&& dst.__ControllerID != CI_ANY && __ControllerID != dst.__ControllerID) return false;
	if (__Variant != IV_ANY			&& dst.__Variant != IV_ANY		&& __Variant != dst.__Variant) return false;
	return true;
}



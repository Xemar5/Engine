#include "Device.h"
#include "Output_Handler.h"
#include "Entity.h"
#include "Sprite.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Keyboard Keyboard::Get;
Sint32 Gamepad::Deadzone = 8000;


void Keyboard::Events_CleanUp()
{
	for (auto it = _Inputs.begin(); it != _Inputs.end();)
	{
		if (it->State == IS_PUSHED) it++->State = SDL_GetTicks();
		else if (it->State == IS_RELEASED) it = _Inputs.erase(it);
		else ++it;
	}
}

void Keyboard::Events()
{
	if (System::Events.type == SDL_KEYDOWN)
		_Inputs.push_back(Input::Set(IT_KEYBOARD_KEY, System::Events.key.keysym.sym, IS_PUSHED));
	if (System::Events.type == SDL_KEYUP)
		for (auto& it : _Inputs)
			if (it == Input::Set(IT_KEYBOARD_KEY, System::Events.key.keysym.sym, IS_ANY)) it.State = IS_RELEASED;


	if (System::Events.type == SDL_MOUSEBUTTONDOWN)
		_Inputs.push_back(Input::Set(IT_MOUSE_BUTTON, System::Events.button.button, IS_PUSHED));
	if (System::Events.type == SDL_MOUSEBUTTONUP)
		for (auto& it : _Inputs)
			if (it == Input::Set(IT_MOUSE_BUTTON, System::Events.button.button, IS_ANY)) it.State = IS_RELEASED;
}

bool Keyboard::Contains_Mouse(Entity* ent)
{
	if (!ent)
	{
		Output_Handler::Error << "ERR Entity::Contains_Mouse : No entity supplied\n";
		return false;
	}
	if (!ent->Get_Sprite())
	{
		Output_Handler::Error << "ERR Entity::Contains_Mouse : Given entity has no sprite supplied\n";
		return false;
	}
	if (!ent->Get_Sprite()->Get_Texture())
	{
		Output_Handler::Error << "ERR Entity::Contains_Mouse : Given sprite has no texture supplied\n";
		return false;
	}
	int px = Mouse::Get[Input::Set(IT_MOUSE_AXIS, MA_X)].Held();
	int py = Mouse::Get[Input::Set(IT_MOUSE_AXIS, MA_Y)].Held();
	auto sp = ent->Get_Sprite();
	double offx = sp->Get_Texture()->Get_SDL_Starting_Point().x * sp->Scale;
	double offy = sp->Get_Texture()->Get_SDL_Starting_Point().y * sp->Scale;
	return (
		px >= ent->X - offx &&
		px <= ent->X - offx + ent->Get_Hitbox().first &&
		py >= ent->Y - offy &&
		py <= ent->Y - offy + ent->Get_Hitbox().second
		);
}







std::vector<std::unique_ptr<Gamepad>> Gamepad::__Gamepads;



void Gamepad::Events_CleanUp()
{
	for (unsigned i = 0; i < __Gamepads.size(); ++i)
		for (auto it = __Gamepads[i]->_Inputs.begin(); it != __Gamepads[i]->_Inputs.end();)
		{
			if (it->State == IS_PUSHED)
			{
				if ((it->Type() & 0b111) == IT_GAMEPAD_AXIS) (Input_State)SDL_JoystickGetAxis(SDL_JoystickFromInstanceID(Input::Which_Controller(it->Type())), it->Key());
				it++->State = SDL_GetTicks();
			}
			else if (it->State == IS_RELEASED) it = __Gamepads[i]->_Inputs.erase(it);
			else ++it;
		}
}

void Gamepad::Events()
{
	if (System::Events.type == SDL_JOYDEVICEADDED)
		Gamepad::Set(System::Events.jdevice.which);

	else if (System::Events.type == SDL_JOYDEVICEREMOVED)
		Gamepad::Get(System::Events.jdevice.which).Remove();



	else if (System::Events.type == SDL_JOYBUTTONDOWN)
		Gamepad::Get(System::Events.jbutton.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_BUTTON | Input::Controller(System::Events.jbutton.which), System::Events.jbutton.button, IS_PUSHED));

	else if (System::Events.type == SDL_JOYBUTTONUP)
	{
		for (auto& it : Gamepad::Get(System::Events.jbutton.which)._Inputs)
			if (it == Input::Set(IT_GAMEPAD_BUTTON | Input::Controller(System::Events.jbutton.which), System::Events.jbutton.button, IS_ANY)) it.State = IS_RELEASED;
	}

	else if (System::Events.type == SDL_JOYHATMOTION)
	{
		Uint8 flag = 0;
		for (auto& it : Gamepad::Get(System::Events.jhat.which)._Inputs)
		{
			if ((it.Type() & 0b111) != IT_GAMEPAD_HAT) continue;
			for (unsigned i = 0; i < 4; ++i)
				if (it.Key() == (1 << i | Input::Hat(System::Events.jhat.hat)))
				{
					if (!(System::Events.jhat.value & 1 << i)) it.State = IS_RELEASED;
					else flag = flag | 1 << i;
					break;
				}
		}
		if (System::Events.jhat.value & ~flag & 1 << 0)
			Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_HAT | Input::Controller(System::Events.jhat.which), 1 << 0 | Input::Hat(System::Events.jhat.hat), IS_PUSHED));
		if (System::Events.jhat.value & ~flag & 1 << 1)
			Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_HAT | Input::Controller(System::Events.jhat.which), 1 << 1 | Input::Hat(System::Events.jhat.hat), IS_PUSHED));
		if (System::Events.jhat.value & ~flag & 1 << 2)
			Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_HAT | Input::Controller(System::Events.jhat.which), 1 << 2 | Input::Hat(System::Events.jhat.hat), IS_PUSHED));
		if (System::Events.jhat.value & ~flag & 1 << 3)
			Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_HAT | Input::Controller(System::Events.jhat.which), 1 << 3 | Input::Hat(System::Events.jhat.hat), IS_PUSHED));
	}

	else if (System::Events.type == SDL_JOYAXISMOTION)
	{
		auto exists = Gamepad::Get(System::Events.jaxis.which)._Inputs.end();
		for (auto it = Gamepad::Get(System::Events.jaxis.which)._Inputs.begin(); it != Gamepad::Get(System::Events.jaxis.which)._Inputs.end(); ++it)
			if (*it == Input::Set(IT_GAMEPAD_AXIS | Input::Controller(System::Events.jaxis.which), System::Events.jaxis.axis, IS_ANY))
			{
				exists = it;
				break;
			}
		if (exists == Gamepad::Get(System::Events.jaxis.which)._Inputs.end() && abs(System::Events.jaxis.value) > Deadzone)
			Gamepad::Get(System::Events.jaxis.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_AXIS | Input::Controller(System::Events.jaxis.which), System::Events.jaxis.axis, IS_PUSHED));
		else if (exists != Gamepad::Get(System::Events.jaxis.which)._Inputs.end() && abs(System::Events.jaxis.value) < Deadzone)
			exists->State = IS_RELEASED;
	}
}

Gamepad& Gamepad::Get(Sint32 index)
{
	if (index < 0) return *__Gamepads[0];
	for (unsigned i = 1; i < __Gamepads.size(); ++i)
		if (__Gamepads[i]->Joystick && index == SDL_JoystickInstanceID(__Gamepads[i]->Joystick))
			return *__Gamepads[i];
	return *__Gamepads[0];
}

bool Gamepad::Set(Sint32 index)
{
	if (index < 0) return false;
	Gamepad::__Gamepads.emplace_back(new Gamepad);
	__Gamepads.back()->Joystick = SDL_JoystickOpen(index);
	std::string joy_name = SDL_JoystickName(__Gamepads.back()->Joystick);
	joy_name.erase(std::remove_if(joy_name.begin(), joy_name.end(), [](int i)->bool { return i < 0 ? true : false; }), joy_name.end());
	for (auto it = Mapping::Maps.begin(); joy_name.size() && it != Mapping::Maps.end(); ++it)
	{
		std::string str = it->first;
		str.erase(std::remove_if(str.begin(), str.end(), [](int i)->bool { return i < 0 ? true : false; }), str.end());
		if (str == joy_name)
		{
			__Gamepads.back()->Bindings = Mapping::Maps.find(it->first)->second;
			return true;
		}
	}
	__Gamepads.back()->Bindings = Mapping::Default_Bindings;
	__Gamepads.back()->Bindings.Save(SDL_JoystickName(__Gamepads.back()->Joystick));

	return true;
}

bool Gamepad::Remove()
{
	for (unsigned i = 1; i < __Gamepads.size(); ++i)
		if (__Gamepads[i].get() == this)
		{
			__Gamepads.erase(__Gamepads.begin() + i);
			return true;
		}
	return false;
}

void Device::Init(std::string path)
{
	Gamepad::__Gamepads.emplace_back(new Gamepad());
	Mapping::Init(path);
	Keyboard::Get.Bindings = Mapping::Maps["Keyboard"];
}

void Device::Events_CleanUp()
{
	Keyboard::Get.Events_CleanUp();
	Gamepad::Get(0).Events_CleanUp();
}

void Device::Events()
{
	Keyboard::Get.Events();
	Gamepad::Get(0).Events();
}

Device & Device::Get(Sint32 index)
{
	if (index < -1 || index >= (int)Gamepad::__Gamepads.size()) return *Gamepad::__Gamepads[0];
	if (index == -1) return Keyboard::Get;
	return Gamepad::Get(index);
}

Sint32 Device::Which()
{
	if (System::Events.type == SDL_KEYDOWN ||
		System::Events.type == SDL_KEYUP ||
		System::Events.type == SDL_MOUSEBUTTONDOWN ||
		System::Events.type == SDL_MOUSEBUTTONUP ||
		System::Events.type == SDL_MOUSEMOTION)
		return KEYBOARD;
	else if (System::Events.type == SDL_JOYBUTTONDOWN ||
		System::Events.type == SDL_JOYBUTTONUP)
		return System::Events.jbutton.which;
	else if (System::Events.type == SDL_JOYAXISMOTION)
		return System::Events.jaxis.which;
	else if (System::Events.type == SDL_JOYHATMOTION)
		return System::Events.jhat.which;
	return -2;
}


Input & Device::operator[](const char * name)
{
	auto b = Bindings[name];
	if (b == Bindings["UNDEFINED"])
		return _Inputs[0];
	for (auto& it : _Inputs)
		if (it == b)
			return it;
	return _Inputs[0];
}

Input & Device::operator[](Input input)
{
	for (auto& it : _Inputs)
		if (input == it)
			return it;

	return _Inputs[0];
}



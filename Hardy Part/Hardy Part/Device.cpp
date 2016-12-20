#include "Device.h"
#include "Output_Handler.h"
#include "Entity.h"
#include "Sprite.h"
#include "Texture.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost\algorithm\string.hpp>

Keyboard Keyboard::Get;
Sint32 Gamepad::Deadzone = 8000;
Input* Device::_CurrentInput = nullptr;
double Keyboard::MouseIdleTime = 100;

void Keyboard::Events_CleanUp()
{
	for (auto it = _Inputs.begin(); it != _Inputs.end();)
	{
		if (it->State == IS_PUSHED)
		{
			it->__Time = SDL_GetTicks();
			it->State = IS_HELD;
			++it;
		}
		else if (it->State == IS_RELEASED)
		{
			it = _Inputs.erase(it);
		}
		else ++it;
	}
}


void Keyboard::Events()
{
	auto kd = Input::Set(IT_KEYBOARD_KEY, System::Events.key.keysym.sym, CI_KEYBOARD_MOUSE, IV_ANY, IS_PUSHED);
	auto ku = Input::Set(IT_KEYBOARD_KEY, System::Events.key.keysym.sym, CI_KEYBOARD_MOUSE, IV_ANY, IS_ANY);
	auto md = Input::Set(IT_MOUSE_BUTTON, System::Events.button.button, CI_KEYBOARD_MOUSE, IV_ANY, IS_PUSHED);
	auto mu = Input::Set(IT_MOUSE_BUTTON, System::Events.button.button, CI_KEYBOARD_MOUSE, IV_ANY, IS_ANY);

	auto mx = Input::Set(IT_MOUSE_AXIS, MA_X, CI_KEYBOARD_MOUSE, IV_ANY, IS_ANY);
	auto mxd = Input::Set(IT_MOUSE_AXIS, MA_X, CI_KEYBOARD_MOUSE, IV_ANY, IS_PUSHED);
	auto my = Input::Set(IT_MOUSE_AXIS, MA_Y, CI_KEYBOARD_MOUSE, IV_ANY, IS_ANY);
	auto myd = Input::Set(IT_MOUSE_AXIS, MA_Y, CI_KEYBOARD_MOUSE, IV_ANY, IS_PUSHED);
	auto ma1 = -1;
	auto ma2 = -1;

	switch (System::Events.type)
	{
	case SDL_KEYDOWN:			_Inputs.push_back(kd); _CurrentInput = &_Inputs.back(); break;
	case SDL_KEYUP:				for (auto& it : _Inputs) if (it == ku) { it.State = IS_RELEASED; _CurrentInput = &it; } break;
	case SDL_MOUSEBUTTONDOWN:	_Inputs.push_back(md); _CurrentInput = &_Inputs.back(); break;
	case SDL_MOUSEBUTTONUP:		for (auto& it : _Inputs) if (it == mu) { it.State = IS_RELEASED; _CurrentInput = &it; } break;
	case SDL_MOUSEMOTION:		
		for(unsigned it = 1; it < _Inputs.size(); ++it)
			{
				if (_Inputs[it] == mx)
					ma1 = it;
				if (_Inputs[it] == my)
					ma2 = it;
			}
		if (System::Events.motion.xrel && ma1 != -1) _Inputs[ma1].__Time = SDL_GetTicks();
		else if (System::Events.motion.xrel && ma1 == -1) _Inputs.push_back(mxd);
		if (System::Events.motion.yrel && ma2 != -1) _Inputs[ma2].__Time = SDL_GetTicks();
		else if (System::Events.motion.yrel && ma2 == -1) _Inputs.push_back(myd);
		_CurrentInput = &Input::Set(IT_MOUSE_AXIS, IK_ANY, CI_KEYBOARD_MOUSE, IV_ANY, IS_ANY);

	default: break;
	}

	//if (System::Events.type == SDL_KEYDOWN)
	//	_Inputs.push_back(kd);
	//if (System::Events.type == SDL_KEYUP)
	//	for (auto& it : _Inputs) if (it == ku) it.State = IS_RELEASED;
	//
	//
	//if (System::Events.type == SDL_MOUSEBUTTONDOWN)
	//	_Inputs.push_back(md);
	//if (System::Events.type == SDL_MOUSEBUTTONUP)
	//	for (auto& it : _Inputs)
	//		if (it == mu) it.State = IS_RELEASED;
}

void Keyboard::Update()
{
	auto x = _Inputs.end();
	auto y = _Inputs.end();
	auto t = SDL_GetTicks();
	for (auto it = _Inputs.begin(); it != _Inputs.end(); ++it)
	{
		if (it->__Type == IT_MOUSE_AXIS && it->__Key == MA_X) x = it;
		if (it->__Type == IT_MOUSE_AXIS && it->__Key == MA_Y) y = it;
	}
	if (x != _Inputs.end() || y != _Inputs.end())
	{
		bool send = false;
		SDL_Event mmove;
		mmove.type = SDL_MOUSEMOTION;
		SDL_GetMouseState(&mmove.motion.x, &mmove.motion.y);
		mmove.motion.xrel = System::Events.motion.xrel;
		mmove.motion.yrel = System::Events.motion.yrel;

		if (x != _Inputs.end() && x->__Time != -1 && t - x->__Time > Keyboard::MouseIdleTime)
		{
			x->State = IS_RELEASED;
			mmove.motion.xrel = 0;
			send = true;
		}
		if (y != _Inputs.end() && y->__Time != -1 && t - y->__Time > Keyboard::MouseIdleTime)
		{
			y->State = IS_RELEASED;
			mmove.motion.yrel = 0;
			send = true;
		}
		if (send)
		{
			SDL_PushEvent(&mmove);
		}
	}

}



bool Keyboard::Contains_Mouse(Entity<> ent)
{
	if (!ent)
	{
		Output_Handler::Error << "ERR Entity::Contains_Mouse : No entity supplied\n";
		return false;
	}
	if (!ent->texture)
	{
		Output_Handler::Error << "ERR Entity::Contains_Mouse : Given entity has no texture supplied\n";
		return false;
	}
	double px = (double)System::Events.motion.x / Screen::Get_Scale();
	double py = (double)System::Events.motion.y / Screen::Get_Scale();
	//double px = Mouse::Get[Input::Set(IT_MOUSE_AXIS, MA_X)].Held();
	//double py = Mouse::Get[Input::Set(IT_MOUSE_AXIS, MA_Y)].Held();
	auto sp = ent->texture;
	double offx = sp->Starting_Point().x * sp->Scale;
	double offy = sp->Starting_Point().y * sp->Scale;
	return (
		px >= ent->X - offx &&
		px <= ent->X - offx + ent->hitbox().first &&
		py >= ent->Y - offy &&
		py <= ent->Y - offy + ent->hitbox().second
		);
}








std::vector<std::unique_ptr<Gamepad>> Gamepad::__Gamepads;



void Gamepad::Events_CleanUp()
{
	for (unsigned i = 0; i < __Gamepads.size(); ++i)
	{
		for (auto it = __Gamepads[i]->_Inputs.begin(); it != __Gamepads[i]->_Inputs.end();)
		{
			if (it->State == IS_PUSHED)
			{
				//auto l = it->Key() >> 2;
				//if ((it->Type() & 0b111) == IT_GAMEPAD_AXIS) (Input_State)SDL_JoystickGetAxis(SDL_JoystickFromInstanceID(Input::Which_Controller(it->Type())), it->Key() >> 2);
				if (it->Type() == IT_GAMEPAD_AXIS)
					it->Value = SDL_JoystickGetAxis(SDL_JoystickFromInstanceID(it->ControllerID()), it->Key());
				it->__Time = SDL_GetTicks();
				it->State = IS_HELD;
				++it;
			}
			else if (it->State == IS_RELEASED) it = __Gamepads[i]->_Inputs.erase(it);
			else ++it;
		}
	}
}

void Gamepad::Handle_Axis()
{
	auto aa = Input::Set(IT_GAMEPAD_AXIS, System::Events.jaxis.axis, System::Events.jaxis.which, IV_ANY, IS_ANY);
	auto ap = Input::Set(IT_GAMEPAD_AXIS, System::Events.jaxis.axis, System::Events.jaxis.which, IV_ANY, IS_PUSHED);
	auto& pad = Gamepad::Get(System::Events.jaxis.which);
	auto end = pad._Inputs.end();
	auto exists = end;

	for (auto it = pad._Inputs.begin(); it != end; ++it)
	{
		if (*it == aa)
		{
			exists = it;
			break;
		}
	}
	if (exists == end && abs(System::Events.jaxis.value) > Deadzone)
	{
		pad._Inputs.push_back(ap);
		pad._CurrentInput = &pad._Inputs.back();
	}
	else if (exists != end && abs(System::Events.jaxis.value) < Deadzone)
	{
		exists->State = IS_RELEASED;
		pad._CurrentInput = exists._Ptr;
	}
}

void Gamepad::Handle_Hat()
{
	Input jh[] =
	{
		Input::Set(IT_GAMEPAD_HAT, HD_U, System::Events.jhat.which, System::Events.jhat.hat, IS_PUSHED),
		Input::Set(IT_GAMEPAD_HAT, HD_R, System::Events.jhat.which, System::Events.jhat.hat, IS_PUSHED),
		Input::Set(IT_GAMEPAD_HAT, HD_D, System::Events.jhat.which, System::Events.jhat.hat, IS_PUSHED),
		Input::Set(IT_GAMEPAD_HAT, HD_L, System::Events.jhat.which, System::Events.jhat.hat, IS_PUSHED)
	};

	Uint8 flag = 0b1111;
	for (auto& it : Gamepad::Get(System::Events.jhat.which)._Inputs)
	{
		if (it.__Type != IT_GAMEPAD_HAT) continue;
		if (it.__Variant != System::Events.jhat.hat) continue;
		for (unsigned i = 0; i < 4; ++i)
		{
			if (it.__Key & (1 << i))
			{
				if (System::Events.jhat.value & (1 << i)) flag = ~(~flag | (1 << i));
				else { it.State = IS_RELEASED; Gamepad::Get(System::Events.jhat.which)._CurrentInput = &it; }
			}
		}
		//for (unsigned i = 0; i < 4; ++i)
		//	if (it.__Key == System::Events.jhat.value)
		//	{
		//		if (!(System::Events.jhat.value & 1 << i)) it.State = IS_RELEASED;
		//		else flag = flag | 1 << i;
		//		break;
		//	}
	}
	for (int i = 0; i < 4; ++i)
		if (flag & (1 << i))
		{
			Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(jh[i]);
			Gamepad::Get(System::Events.jhat.which)._CurrentInput = &Gamepad::Get(System::Events.jhat.which)._Inputs.back();
		}
}

void Gamepad::Events()
{
	auto jd = Input::Set(IT_GAMEPAD_BUTTON, System::Events.jbutton.button, System::Events.jbutton.which, IV_ANY, IS_PUSHED);
	auto ju = Input::Set(IT_GAMEPAD_BUTTON, System::Events.jbutton.button, System::Events.jbutton.which, IV_ANY, IS_ANY);
	switch (System::Events.type)
	{
	case SDL_JOYDEVICEADDED:	Gamepad::Set(System::Events.jdevice.which); break;
	case SDL_JOYDEVICEREMOVED:	Gamepad::Remove(System::Events.jdevice.which); break;
	case SDL_JOYBUTTONDOWN:		Gamepad::Get(System::Events.jbutton.which)._Inputs.push_back(jd); Gamepad::Get(System::Events.jbutton.which)._CurrentInput = &Gamepad::Get(System::Events.jbutton.which)._Inputs.back(); break;
	case SDL_JOYBUTTONUP:		for (auto& it : Gamepad::Get(System::Events.jbutton.which)._Inputs) if (it == ju) { it.State = IS_RELEASED; Gamepad::Get(System::Events.jbutton.which)._CurrentInput = &it; } break;
	case SDL_JOYAXISMOTION:		Handle_Axis(); break;
	case SDL_JOYHATMOTION:		Handle_Hat(); break;
	default: break;
	}

	//if (System::Events.type == SDL_JOYDEVICEADDED)
	//	Gamepad::Set(System::Events.jdevice.which);
	//else if (System::Events.type == SDL_JOYDEVICEREMOVED)
	//	Gamepad::Get(System::Events.jdevice.which).Remove();
	//else if (System::Events.type == SDL_JOYBUTTONDOWN)
	//	Gamepad::Get(System::Events.jbutton.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_BUTTON | Input::Controller(System::Events.jbutton.which), System::Events.jbutton.button, IS_PUSHED));
	//else if (System::Events.type == SDL_JOYBUTTONUP)
	//{
	//	for (auto& it : Gamepad::Get(System::Events.jbutton.which)._Inputs)
	//		if (it == Input::Set(IT_GAMEPAD_BUTTON | Input::Controller(System::Events.jbutton.which), System::Events.jbutton.button, IS_ANY)) it.State = IS_RELEASED;
	//}
	//else if (System::Events.type == SDL_JOYHATMOTION)
	//{
	//	Uint8 flag = 0;
	//	for (auto& it : Gamepad::Get(System::Events.jhat.which)._Inputs)
	//	{
	//		if ((it.Type() & 0b111) != IT_GAMEPAD_HAT) continue;
	//		for (unsigned i = 0; i < 4; ++i)
	//			if (it.Key() == (1 << i | Input::Hat(System::Events.jhat.hat)))
	//			{
	//				if (!(System::Events.jhat.value & 1 << i)) it.State = IS_RELEASED;
	//				else flag = flag | 1 << i;
	//				break;
	//			}
	//	}
	//	for (int i = 0; i < 4; ++i)
	//		if (System::Events.jhat.value & ~flag & 1 << i) Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(jh[i]);
	//	//if (System::Events.jhat.value & ~flag & 1 << 0)
	//	//	Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_HAT | Input::Controller(System::Events.jhat.which), 1 << 0 | Input::Hat(System::Events.jhat.hat), IS_PUSHED));
	//	//if (System::Events.jhat.value & ~flag & 1 << 1)
	//	//	Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_HAT | Input::Controller(System::Events.jhat.which), 1 << 1 | Input::Hat(System::Events.jhat.hat), IS_PUSHED));
	//	//if (System::Events.jhat.value & ~flag & 1 << 2)
	//	//	Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_HAT | Input::Controller(System::Events.jhat.which), 1 << 2 | Input::Hat(System::Events.jhat.hat), IS_PUSHED));
	//	//if (System::Events.jhat.value & ~flag & 1 << 3)
	//	//	Gamepad::Get(System::Events.jhat.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_HAT | Input::Controller(System::Events.jhat.which), 1 << 3 | Input::Hat(System::Events.jhat.hat), IS_PUSHED));
	//}
	//else if (System::Events.type == SDL_JOYAXISMOTION)
	//{
	//	auto exists = Gamepad::Get(System::Events.jaxis.which)._Inputs.end();
	//	for (auto it = Gamepad::Get(System::Events.jaxis.which)._Inputs.begin(); it != Gamepad::Get(System::Events.jaxis.which)._Inputs.end(); ++it)
	//		if (*it == Input::Set(IT_GAMEPAD_AXIS | Input::Controller(System::Events.jaxis.which), System::Events.jaxis.axis, IS_ANY))
	//		{
	//			exists = it;
	//			break;
	//		}
	//	if (exists == Gamepad::Get(System::Events.jaxis.which)._Inputs.end() && abs(System::Events.jaxis.value) > Deadzone)
	//		Gamepad::Get(System::Events.jaxis.which)._Inputs.push_back(Input::Set(IT_GAMEPAD_AXIS | Input::Controller(System::Events.jaxis.which), System::Events.jaxis.axis, IS_PUSHED));
	//	else if (exists != Gamepad::Get(System::Events.jaxis.which)._Inputs.end() && abs(System::Events.jaxis.value) < Deadzone)
	//		exists->State = IS_RELEASED;
	//}
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
	__Gamepads.back()->__OpenedIndex = index;
	std::string joy_name = SDL_JoystickName(__Gamepads.back()->Joystick);
	std::cout << SDL_JoystickInstanceID(__Gamepads.back()->Joystick);
	joy_name.erase(std::remove_if(joy_name.begin(), joy_name.end(), [](int i)->bool { return i < 0 ? true : false; }), joy_name.end());
	__Gamepads.back()->_Name = joy_name;
	for (auto p : Player::Get_Players())
		if (p->__ControllerName == joy_name)
			p->Controller = SDL_JoystickInstanceID(__Gamepads.back()->Joystick);
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

bool Gamepad::Remove(Sint32 index)
{
	for (unsigned i = 1; i < __Gamepads.size(); ++i)
		if (__Gamepads[i]->SDL_InstanceID() == index)
		{
			SDL_JoystickClose(__Gamepads[i]->Joystick);
			__Gamepads.erase(__Gamepads.begin() + i);
			return true;
		}
	return false;
}


void Device::Init(std::string path)
{
	Gamepad::__Gamepads.emplace_back(new Gamepad());
	Mapping::Init(path);
	Keyboard::Get.Bindings = Mapping::Maps[Keyboard::Get.Name()];
}

void Device::Events_CleanUp()
{
	Keyboard::Get.Events_CleanUp();
	Gamepad::Get(0).Events_CleanUp();
	Device::_CurrentInput = nullptr;
}

void Device::Events()
{
	Keyboard::Get.Events();
	Gamepad::Get(0).Events();
	//switch (System::Events.type)
	//{
	//case SDL_MOUSEBUTTONDOWN: break;
	//case SDL_MOUSEBUTTONUP: break;
	//case SDL_MOUSEMOTION: break;
	//case SDL_KEYDOWN: break;
	//case SDL_KEYUP: break;
	//case SDL_JOYBUTTONDOWN: break;
	//case SDL_JOYBUTTONUP: break;
	//case SDL_JOYAXISMOTION: break;
	//case SDL_JOYHATMOTION: break;
	//default:
	//	Device::GetCurrent()._CurrentInput = nullptr;
	//	break;
	//}
}


Device & Device::Get(Sint32 index)
{
	if (index < -1) return *Gamepad::__Gamepads[0];
	if (index == -1) return Keyboard::Get;
	return Gamepad::Get(index);
}

Device & Device::Get(std::string name)
{
	if(boost::iequals(name, "keyboard") || boost::iequals(name, "mouse")) return Keyboard::Get;
	for (unsigned i = 1; i < Gamepad::__Gamepads.size(); ++i)
	{
		if (boost::iequals(name, Gamepad::__Gamepads[i]->_Name)) return *Gamepad::__Gamepads[i];
	}
	return *Gamepad::__Gamepads[0];
}

Sint32 Device::Which()
{
	if (System::Events.type == SDL_KEYDOWN ||
		System::Events.type == SDL_KEYUP ||
		System::Events.type == SDL_MOUSEBUTTONDOWN ||
		System::Events.type == SDL_MOUSEBUTTONUP ||
		System::Events.type == SDL_MOUSEMOTION)
		return CI_KEYBOARD_MOUSE;
	else if (System::Events.type == SDL_JOYBUTTONDOWN ||
		System::Events.type == SDL_JOYBUTTONUP)
		return System::Events.jbutton.which;
	else if (System::Events.type == SDL_JOYAXISMOTION)
		return System::Events.jaxis.which;
	else if (System::Events.type == SDL_JOYHATMOTION)
		return System::Events.jhat.which;
	return CI_UNDEFINED;
}

std::vector<Device*> Device::All()
{
	auto v = std::vector<Device*>(Gamepad::__Gamepads.size());
	v[0] = &Keyboard::Get;
	for (unsigned i = 1; i < Gamepad::__Gamepads.size(); ++i)
		v[i] = Gamepad::__Gamepads[i].get();
	return v;
}


void Device::ClearInputs()
{
	while (_Inputs.size() > 1)
	{
		if (Device::_CurrentInput && *Device::_CurrentInput == _Inputs.back())
			Device::_CurrentInput = nullptr;
		_Inputs.pop_back();
	}
}

void Device::ClearAllDeviceInput()
{
	for (auto d : Device::All())
		d->ClearInputs();
	Device::_CurrentInput = nullptr;
}

Input & Device::operator[](const char * name)
{
	auto b = Bindings[name];
	if (b == Bindings["UNDEFINED"])
		return _Inputs[0];
	//for (auto& it : _Inputs)
	//	if (it == b)
	//		return it;
	//return _Inputs[0];
	return operator[](b);
}

Input & Device::operator[](Input input)
{
	for (auto& it : _Inputs)
		if (input == it)
			return it;

	return _Inputs[0];
}



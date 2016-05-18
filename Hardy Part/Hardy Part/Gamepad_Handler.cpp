#include "Output_Handler.h"
#include "Gamepad_Handler.h"
#include "System.h"

std::vector<std::shared_ptr<Gamepad_Handler>> Gamepad_Handler::__Gamepads;

Gamepad_Handler * Gamepad_Handler::Set(int gamepad_index)
{
	if (gamepad_index < 0 || gamepad_index >= SDL_NumJoysticks())
	{
		Output_Handler::Error << "ERR Gamepad_Handler::Set : No gamepad connected with given index (connected gamepads: " << SDL_NumJoysticks() << ", given index: " << gamepad_index + 1 << ")\n";
		return nullptr;
	}
	if (auto joy = Gamepad_Handler::Get(gamepad_index)) return joy;
	Gamepad_Handler::__Gamepads.emplace_back(std::make_shared<Gamepad_Handler>());
	Gamepad_Handler::__Gamepads.back().get()->__Joystick = SDL_JoystickOpen(gamepad_index);
	Gamepad_Handler::__Gamepads.back().get()->__Index = gamepad_index;
	return Gamepad_Handler::__Gamepads.back().get();
}

bool Gamepad_Handler::Remove(int gamepad_index)
{
	auto joy_index = Gamepad_Handler::__Get_Gamepads_Index(gamepad_index);
	if (joy_index == -1)
	{
		Output_Handler::Output << "MSG Gamepad_Handler::Remove : No gamepad connected with given index (connected gamepads: " << SDL_NumJoysticks() << ", given index: " << gamepad_index + 1 << ")\n";
		return false;
	}
	SDL_JoystickClose(Gamepad_Handler::__Gamepads[joy_index]->Get_Joystick());
	Gamepad_Handler::__Gamepads.erase(Gamepad_Handler::__Gamepads.begin() + Gamepad_Handler::__Get_Gamepads_Index(gamepad_index));
	return true;
}

Gamepad_Handler * Gamepad_Handler::Get(int gamepad_index)
{
	if (gamepad_index < 0 || gamepad_index >= SDL_NumJoysticks())
	{
		//Output_Handler::Error << "ERR Gamepad_Handler::Set : No gamepad connected with given index (connected gamepads: " << SDL_NumJoysticks() << ", given index: " << gamepad_index + 1 << ")\n";
		return nullptr;
	}
	for (unsigned i = 0; i < __Gamepads.size(); i++)
	{
		if (__Gamepads[i]->__Index == gamepad_index) return __Gamepads[i].get();
	}
	//Output_Handler::Error << "ERR Gamepad_Handler::Get : No gamepad handler with given index\n";
	return nullptr;
}

unsigned Gamepad_Handler::Gamepad_Count()
{
	return __Gamepads.size();
}

double Gamepad_Handler::Get_Axis_State(std::vector<Sint32> args)
{
	auto it = args.begin();

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Get_Axis_State : Gamepad not supplied \n"; return 0.0; }
	Gamepad_Handler* joy = Gamepad_Handler::Get((int)*it++);
	if (!joy) { /*Output_Handler::Error << "ERR Gamepad_Handler::Get_Axis_State : Gamepad not set (use Gamepad_Handler::Set function)\n";*/ return 0.0; }
	if (!joy->Get_Joystick()) { Output_Handler::Error << "ERR Gamepad_Handler::Get_Axis_State : No gamepad supplied\n"; return 0.0; }

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Get_Axis_State : Given axis doesn't exist\n"; return 0.0; }
	Sint32 axis = (Sint32)*it++;



	double stt = (double)SDL_JoystickGetAxis(joy->Get_Joystick(), axis);
	double dead_zone = 6000.0 * (stt > 0 ? 1. : -1.);

	if (stt == 32767.) return 1.;
	if (abs(stt) < abs(dead_zone)) return 0.;
	return (stt - dead_zone) / (32768.0 - abs(dead_zone));
}

double Gamepad_Handler::Get_Axis_State_Positive(std::vector<Sint32> args)
{
	double val = Gamepad_Handler::Get_Axis_State(args);
	if (val > 0.0) return val;
	return 0.0;
}

double Gamepad_Handler::Get_Axis_State_Negative(std::vector<Sint32> args)
{
	double val = Gamepad_Handler::Get_Axis_State(args);
	if (val < 0.0) return -val;
	return 0.0;
}

double Gamepad_Handler::Get_Absolute_Axis_State(std::vector<Sint32> args)
{
	auto it = args.begin();

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Get_Absolute_Axis_State : Gamepad not supplied\n"; return 0.0; }
	Gamepad_Handler* joy = Gamepad_Handler::Get((int)*it++);
	if (!joy) { Output_Handler::Error << "ERR Gamepad_Handler::Get_Absolute_Axis_State : Gamepad not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	if (!joy->Get_Joystick()) { Output_Handler::Error << "ERR Gamepad_Handler::Get_Absolute_Axis_State : No gamepad supplied\n"; return 0.0; }

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Get_Absolute_Axis_State : Given axis doesn't exist\n"; return 0.0; }
	Sint32 axis = (Sint32)*it++;

	double as = SDL_JoystickGetAxis(joy->Get_Joystick(), axis);
	double dead_zone = 6000.0 * (as > 0 ? 1. : -1.);
	if (abs(as) < abs(dead_zone)) return 0;
	return (as - dead_zone) / (32768.0 - abs(dead_zone)) * 32768.0;
}

double Gamepad_Handler::Get_Absolute_Axis_State_Positive(std::vector<Sint32> args)
{
	double val = Gamepad_Handler::Get_Absolute_Axis_State(args);
	if (val > 0.0) return val;
	return 0.0;
}

double Gamepad_Handler::Get_Absolute_Axis_State_Negative(std::vector<Sint32> args)
{
	double val = Gamepad_Handler::Get_Absolute_Axis_State(args);
	if (val < 0.0) return -val;
	return 0.0;
}

double Gamepad_Handler::Button_Down(std::vector<Sint32> args)
{
	auto it = args.begin();

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Down : Gamepad not supplied\n"; return 0.0; }
	Gamepad_Handler* joy = Gamepad_Handler::Get((int)*it++);
	if (!joy) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Down : Gamepad not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	if (!joy->Get_Joystick()) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Down : No gamepad supplied\n"; return 0.0; }

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Down : Button not supplied\n"; return 0.0; }
	Sint32 button = (Sint32)*it++;


	for (std::map<Uint8, int>::iterator it = joy->__Map.begin(); it != joy->__Map.end(); it++)
		if (it->first == button && it->second == -2)
			return true;
	return false;
}

double Gamepad_Handler::Button_Up(std::vector<Sint32> args)
{
	auto it = args.begin();

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Up : Gamepad not supplied\n"; return 0.0; }
	Gamepad_Handler* joy = Gamepad_Handler::Get((int)*it++);
	if (!joy) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Up : Gamepad not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	if (!joy->Get_Joystick()) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Up : No gamepad supplied\n"; return 0.0; }

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Up : Button not supplied\n"; return 0.0; }
	Sint32 button = (Sint32)*it++;


	for (std::map<Uint8, int>::iterator it = joy->__Map.begin(); it != joy->__Map.end(); it++)
		if (it->first == button && it->second == -1)
			return true;
	return false;
}

double Gamepad_Handler::Button_Held(std::vector<Sint32> args)
{
	auto it = args.begin();

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Held : Gamepad not supplied\n"; return 0.0; }
	Gamepad_Handler* joy = Gamepad_Handler::Get((int)*it++);
	if (!joy) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Held : Gamepad not set (use Gamepad_Handler::Set function)\n"; return 0.0; }
	if (!joy->Get_Joystick()) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Held : No gamepad supplied\n"; return 0.0; }

	if (it == args.end()) { Output_Handler::Error << "ERR Gamepad_Handler::Button_Held : Button not supplied\n"; return 0.0; }
	Sint32 button = (Sint32)*it++;


	Sint32 time;
	if (it == args.end()) time = 0;
	else time = (Sint32)*it++;



	for (std::map<Uint8, int>::iterator it = joy->__Map.begin(); it != joy->__Map.end(); it++)
		if (it->first == button && it->second >= 0 && SDL_GetTicks() - it->second >= (Uint32)time)
			return true;
	return false;
}




int Gamepad_Handler::Get_Index()
{
	return __Index;
}

int Gamepad_Handler::Get_SDL_Index()
{
	return SDL_JoystickInstanceID(Get_Joystick());
}

SDL_Joystick * Gamepad_Handler::Get_Joystick()
{
	return __Joystick;
}

std::vector<std::shared_ptr<Gamepad_Handler>> Gamepad_Handler::Get_Gamepads()
{
	return __Gamepads;
}

void Gamepad_Handler::__Events()
{
	if (System::Events.type == 1541)
		Gamepad_Handler::Set(System::Events.cdevice.which);
	if (System::Events.type == 1542)
	{
		for (unsigned i = 0; i < Gamepad_Count(); i++)
		{
			if (SDL_JoystickInstanceID(__Gamepads[i]->Get_Joystick()) == System::Events.cdevice.which)
			{
				Gamepad_Handler::Remove(__Gamepads[i]->Get_Index());
				break;
			}
		}
	}

	for (unsigned i = 0; i < Gamepad_Count(); i++)
	{
		if (System::Events.type == SDL_JOYBUTTONDOWN)
			Gamepad_Handler::__Gamepads[i]->__Map.insert(std::make_pair(System::Events.jbutton.button, -2));
		if (System::Events.type == SDL_JOYBUTTONUP)
			for (std::map<Uint8, int>::iterator it = Gamepad_Handler::__Gamepads[i]->__Map.begin(); it != Gamepad_Handler::__Gamepads[i]->__Map.end(); it++)
				if (it->first == System::Events.jbutton.button)
					it->second = -1;
	}
}

void Gamepad_Handler::__Update()
{
	for (unsigned i = 0; i < Gamepad_Count(); i++)
	{
		for (std::map<Uint8, int>::iterator it = Gamepad_Handler::__Gamepads[i]->__Map.begin(); it != Gamepad_Handler::__Gamepads[i]->__Map.end();)
		{
			if (it->second == -1)
			{
				auto temp = it;
				++it;
				Gamepad_Handler::__Gamepads[i]->__Map.erase(temp);
			}
			else if (it->second == -2)
			{
				it->second = SDL_GetTicks();
				++it;
			}
			else ++it;
		}
	}
}

int Gamepad_Handler::__Get_Gamepads_Index(int gamepad_index)
{
	int i = 0;
	while ((unsigned)i < __Gamepads.size())
	{
		if (__Gamepads[i]->__Index == gamepad_index) return i;
		++i;
	}
	Output_Handler::Output << "MSG Gamepad_Handler::__Get_Gamepads_Index : No gamepad with given index connected\n";
	return -1;
}

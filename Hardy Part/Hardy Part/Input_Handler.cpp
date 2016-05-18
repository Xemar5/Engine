#include "Input_Handler.h"
#include "Keyboard_Handler.h"
#include "Gamepad_Handler.h"
#include "Mouse_Handler.h"
#include "Player.h"
#include "Output_Handler.h"
#include <string>
#include <boost\regex.hpp>

std::map<std::string, std::shared_ptr<Input_Handler>> Input_Handler::Empty_Preset =
{
	{ "a", nullptr },
	{ "b", nullptr },
	{ "x", nullptr },
	{ "y", nullptr },

	{ "r1", nullptr },
	{ "r2", nullptr },
	{ "r3", nullptr },
	{ "l1", nullptr },
	{ "l2", nullptr },
	{ "l3", nullptr },

	{ "select", nullptr },
	{ "start", nullptr },

	{ "laup", nullptr },
	{ "ladown", nullptr },
	{ "laleft", nullptr },
	{ "laright", nullptr },

	{ "raup", nullptr },
	{ "radown", nullptr },
	{ "raleft", nullptr },
	{ "raright", nullptr },

	{ "dup", nullptr },
	{ "ddown", nullptr },
	{ "dleft", nullptr },
	{ "dright", nullptr }

};


std::shared_ptr<Input_Handler> Input_Handler::Set(double(*input_foo)(std::vector<Sint32>), std::vector<Sint32> arg_list)
{
	if (!input_foo)
	{
		Output_Handler::Error << "ERR Input_Handler::Set : No Input Function supplied\n";
		return nullptr;
	}
	if (!arg_list.size())
	{
		Output_Handler::Error << "ERR Input_Handler::Set : No Arg List supplied\n";
		return nullptr;
	}

	std::shared_ptr<Input_Handler> ih = std::make_shared<Input_Handler>();
	ih->Input_Function = input_foo;
	ih->Input_Args = arg_list;
	return ih;
}

Input_Preset Input_Handler::Load(std::istream& is, std::string controller_name, int controller_index)
{
	std::string file;

	is.seekg(0, std::ios::end);
	file.resize((unsigned)is.tellg());
	is.seekg(0, std::ios::beg);
	is.read(&file[0], file.size());

	std::size_t iter = file.find("[" + controller_name + "]");
	if (iter == std::string::npos)
	{
		Output_Handler::Error << "ERR Input_Handler::Load : No controller key preset with given name found\n";
		return Input_Handler::Empty_Preset;
	}
	file = file.substr(iter + controller_name.length() + 2, file.length() - controller_name.length() - 2);

	iter = file.find('[');
	if (iter != std::string::npos) file = file.substr(0, iter);


	Input_Preset ip = Input_Handler::Empty_Preset;
	for (auto& k : ip)
	{
		std::size_t kpos = file.find("\n" + k.first);
		if (kpos == std::string::npos) continue;

		std::size_t npos = file.find('\n', kpos + 1);
		kpos = file.find('=', kpos);
		if (npos == std::string::npos) npos = file.length();
		if (kpos == std::string::npos || kpos + 1 >= npos) continue;

		k.second = __Decode_Load(file.substr(kpos + 1, npos - kpos - 1), controller_index);
	}

	return ip;
	//Input_Preset m = Input_Handler::Empty_Preset;
	//std::string s;
	//while (std::getline(is, s))
	//{
	//	std::size_t fspc = s.find(' ');
	//	std::size_t feq = s.find('=');
	//	if (fspc == std::string::npos && feq == std::string::npos)
	//	{
	//		Output_Handler::Error << "ERR Input_Handler::Load : No key name found\n";
	//		continue;
	//	}
	//	auto action = m.find(s.substr(0, fspc > feq ? feq : fspc));
	//	if (action == m.end())
	//	{
	//		Output_Handler::Error << "ERR Input_Handler::Load : Supplied key (" << s.substr(0, fspc > feq ? feq : fspc) << ") doesn't exist\n";
	//		continue;
	//	}
	//	std::size_t occur = s.rfind("controller");
	//	if (occur != std::string::npos)
	//	{
	//		std::string subs = s.substr(occur + 10, s.length() - occur - 10);
	//		if (subs.length() == 0)
	//		{
	//			Output_Handler::Error << "ERR Input_Handler::Load : No button/gamepad index supplied\n";
	//			continue;
	//		}
	//
	//		Sint8 index = -1;
	//		for (unsigned i = 0; i < subs.length(); ++i)
	//		{
	//			if (subs[i] == '_')
	//			{
	//				subs = subs.substr(i + 1, subs.length() - i - 1);
	//				break;
	//			}
	//			if (subs[i] < '0' || subs[i] > '9') break;
	//			if (index < 0) index = 0;
	//			index = index * 10 + (subs[i] - '0');
	//		}
	//		if (index == -1)
	//		{
	//			Output_Handler::Error << "ERR Input_Handler::Load : No gamepad index supplied\n";
	//			continue;
	//		}
	//
	//		auto axis = subs.find("axis");
	//		if (axis != std::string::npos)
	//		{
	//			subs.substr(axis + 4, subs.length() - axis - 4);
	//		}
	//
	//		SDL_GameControllerButton btn = SDL_GameControllerGetButtonFromString(subs.c_str());
	//		if (btn == SDL_CONTROLLER_BUTTON_INVALID)
	//		{
	//			Output_Handler::Error << "ERR Input_Handler::Load : Supplied button doesn't exist\n";
	//			continue;
	//		}
	//
	//
	//		auto ih = Input_Handler::Set(Gamepad_Handler::Button_Down, { (Sint32)btn, (Sint32)index });
	//		action->second = ih;
	//		continue;
	//	}
	//
	//	occur = s.rfind("keyboard_");
	//	if (occur != std::string::npos)
	//	{
	//		std::string subs = s.substr(occur + 9, s.length() - occur - 9);
	//		SDL_Keycode k = SDL_GetKeyFromName(subs.c_str());
	//		if (k == SDLK_UNKNOWN)
	//		{
	//			Output_Handler::Output << "MSG Input_Handler::Load : Unknown keyboard button (" << subs << ")\n";
	//			continue;
	//		}
	//		auto ih = Input_Handler::Set(Keyboard_Handler::Key_Down, { (Sint32)k });
	//		action->second = ih;
	//		continue;
	//	}
	//}
	//return m;
}






std::shared_ptr<Input_Handler> __Decode_Gamepad(std::shared_ptr<Input_Handler> ih, std::string str, int controller_index)
{
	if (!ih) return ih = nullptr;
	if (!str.length()) return ih = nullptr;
	if (controller_index < 0) return ih = nullptr;

	unsigned short int flag = 0;
	if (str.find("button") != std::string::npos)	flag = flag | 1 << 0;
	if (str.find("axis") != std::string::npos)		flag = flag | 1 << 1;

	std::vector<int> v;
	std::size_t bpos = 0;
	while (true)
	{
		std::string s = boost::regex_replace(str.substr(bpos, str.length() - bpos), boost::regex("[^0-9]*([0-9]+).*"), std::string("\\1"));
		if (!s.length() || s == str.substr(bpos, str.length() - bpos)) break;
		bpos = str.find(s.back()) + 1;
		v.push_back(std::stoi(s));
	}
	bpos = 0;
	while (true)
	{
		bpos = str.substr(bpos, str.length() - bpos).find("SDL_");
		if (bpos == std::string::npos) break;
		std::size_t epos = str.substr(bpos, str.length() - bpos).find(" ");
		if (epos == std::string::npos) epos = str.substr(bpos, str.length() - bpos).length();
		bpos += 4;

		int code;
		std::string seq = str.substr(bpos, epos - 4);

		code = SDL_GameControllerGetButtonFromString(seq.c_str());
		if (code != SDL_CONTROLLER_BUTTON_INVALID)
		{
			v.push_back(code);
			continue;
		}
		code = SDL_GameControllerGetAxisFromString(seq.c_str());
		if (code != SDL_CONTROLLER_AXIS_INVALID)
		{
			v.push_back(code);
			continue;
		}
		Output_Handler::Error << "ERR Input_Handler::__Decode_Gamepad : Error reading sdl-type key (" << str.substr(bpos, epos) << ")\n";
	}
	if (!v.size()) return ih = nullptr;

	//if "button"
	if (!(flag ^ (1 << 0)))
	{
		if (str.find("down") != std::string::npos)	flag = flag | 1 << 2;
		if (str.find("up") != std::string::npos)	flag = flag | 1 << 3;
		if (str.find("held") != std::string::npos)	flag = flag | 1 << 4;
	}

	//if "axis"
	else if (!(flag ^ (1 << 1)))
	{
		if (str.find("unit ") != std::string::npos)			flag = flag | 1 << 2;
		if (str.find("unit_positive") != std::string::npos)	flag = flag | 1 << 3;
		if (str.find("unit_negative") != std::string::npos) flag = flag | 1 << 4;

		if (str.find("abs ") != std::string::npos)			flag = flag | 1 << 5;
		if (str.find("abs_positive") != std::string::npos)	flag = flag | 1 << 6;
		if (str.find("abs_negative") != std::string::npos)	flag = flag | 1 << 7;
	}

	else return ih = nullptr;



	if		(!(flag ^ (1 << 0 | 1 << 2))) ih->Input_Function = Gamepad_Handler::Button_Down;
	else if (!(flag ^ (1 << 0 | 1 << 3))) ih->Input_Function = Gamepad_Handler::Button_Up;
	else if (!(flag ^ (1 << 0 | 1 << 4))) ih->Input_Function = Gamepad_Handler::Button_Held;

	else if (!(flag ^ (1 << 1 | 1 << 2))) ih->Input_Function = Gamepad_Handler::Get_Axis_State;
	else if (!(flag ^ (1 << 1 | 1 << 3))) ih->Input_Function = Gamepad_Handler::Get_Axis_State_Positive;
	else if (!(flag ^ (1 << 1 | 1 << 4))) ih->Input_Function = Gamepad_Handler::Get_Axis_State_Negative;
	else if (!(flag ^ (1 << 1 | 1 << 5))) ih->Input_Function = Gamepad_Handler::Get_Absolute_Axis_State;
	else if (!(flag ^ (1 << 1 | 1 << 6))) ih->Input_Function = Gamepad_Handler::Get_Absolute_Axis_State_Positive;
	else if (!(flag ^ (1 << 1 | 1 << 7))) ih->Input_Function = Gamepad_Handler::Get_Absolute_Axis_State_Negative;

	else return ih = nullptr;

	if (str.find("held") != std::string::npos && v.size() < 2) v.push_back(0);
	v.insert(v.begin(), controller_index);
	ih->Input_Args = v;

	return ih;
}
std::shared_ptr<Input_Handler> __Decode_Keyboard(std::shared_ptr<Input_Handler> ih, std::string str)
{
	if (!ih) return nullptr;
	if (!str.length()) return nullptr;

	unsigned short int flag = 0;
	std::vector<int> v;
	std::size_t bpos = 0;
	while (true)
	{
		std::string s = boost::regex_replace(str.substr(bpos, str.length() - bpos), boost::regex("[^0-9]*([0-9]+).*"), std::string("\\1"));
		if (!s.length() || s == str.substr(bpos, str.length() - bpos)) break;
		bpos = str.find(s.back()) + 1;
		v.push_back(std::stoi(s));
	}
	bpos = 0;
	while (true)
	{
		bpos = str.substr(bpos, str.length() - bpos).find("SDL_");
		if (bpos == std::string::npos) break;
		std::size_t epos = str.substr(bpos, str.length() - bpos).find(" ");
		if (epos == std::string::npos) epos = str.substr(bpos, str.length() - bpos).length();
		bpos += 4;

		int code;
		std::string seq = str.substr(bpos, epos - 4);
		code = SDL_GetKeyFromName(seq.c_str());
		if (code != SDLK_UNKNOWN)
		{
			v.push_back(code);
			continue;
		}

		Output_Handler::Error << "ERR Input_Handler::__Decode_Keyboard : Error reading sdl-type key (" << str.substr(bpos, epos) <<")\n";
	}
	if (!v.size()) return ih = nullptr;

	if (str.find("down") != std::string::npos)	flag = flag | 1 << 2;
	if (str.find("up") != std::string::npos)	flag = flag | 1 << 3;
	if (str.find("held") != std::string::npos)	flag = flag | 1 << 4;

	if		(!(flag ^ (1 << 2))) ih->Input_Function = Keyboard_Handler::Key_Down;
	else if (!(flag ^ (1 << 3))) ih->Input_Function = Keyboard_Handler::Key_Up;
	else if (!(flag ^ (1 << 4))) ih->Input_Function = Keyboard_Handler::Key_Held;
	else return ih = nullptr;

	if (str.find("held") != std::string::npos && v.size() < 2) v.push_back(0);
	ih->Input_Args = v;

	return ih;
}
std::shared_ptr<Input_Handler> __Decode_Mouse(std::shared_ptr<Input_Handler> ih, std::string str)
{
	if (!ih) return ih = nullptr;
	if (!str.length()) return ih = nullptr;

	unsigned short int flag = 0;
	if (str.find("button") != std::string::npos)	flag = flag | 1 << 0;
	if (str.find("relative_") != std::string::npos)	flag = flag | 1 << 1;

	std::vector<int> v;
	std::size_t bpos = 0;
	while (true)
	{
		std::string s = boost::regex_replace(str.substr(bpos, str.length() - bpos), boost::regex("[^0-9]*([0-9]+).*"), std::string("\\1"));
		if (!s.length() || s == str.substr(bpos, str.length() - bpos)) break;
		bpos = str.find(s.back()) + 1;
		v.push_back(std::stoi(s));
	}
	//if (!v.size()) return ih = nullptr;

	//if "button"
	if (!(flag ^ (1 << 0)))
	{
		if (str.find("down") != std::string::npos)	flag = flag | 1 << 2;
		if (str.find("up") != std::string::npos)	flag = flag | 1 << 3;
		if (str.find("held") != std::string::npos)	flag = flag | 1 << 4;
	}

	//if "motion"
	else if (!(flag ^ (1 << 1)))
	{
		if (str.find("relative_x") != std::string::npos)	flag = flag | 1 << 2;
		if (str.find("relative_y") != std::string::npos)	flag = flag | 1 << 3;
	}

	else return ih = nullptr;



	if		(!(flag ^ (1 << 0 | 1 << 2))) ih->Input_Function = Mouse_Handler::Button_Down;
	else if (!(flag ^ (1 << 0 | 1 << 3))) ih->Input_Function = Mouse_Handler::Button_Up;
	else if (!(flag ^ (1 << 0 | 1 << 4))) ih->Input_Function = Mouse_Handler::Button_Held;

	else if (!(flag ^ (1 << 1 | 1 << 2))) ih->Input_Function = Mouse_Handler::Get_Relative_Mouse_X_State;
	else if (!(flag ^ (1 << 1 | 1 << 3))) ih->Input_Function = Mouse_Handler::Get_Relative_Mouse_Y_State;

	else return ih = nullptr;

	if (str.find("relative_x") != std::string::npos ||
		str.find("relative_y") != std::string::npos)
	{
		v.push_back(0);
		v.push_back(0);
	}
	if (str.find("held") != std::string::npos && v.size() < 2) v.push_back(0);
	ih->Input_Args = v;

	return ih;
}

std::shared_ptr<Input_Handler> Input_Handler::__Decode_Load(std::string str, int controller_index)
{
	std::shared_ptr<Input_Handler> ih = std::make_shared<Input_Handler>();

	std::size_t isG = str.find("gamepad");
	std::size_t isK = str.find("keyboard");
	std::size_t isM = str.find("mouse");
	unsigned char flag = 0;
	if (isG != std::string::npos) flag = flag | 1 << 0;
	if (isK != std::string::npos) flag = flag | 1 << 1;
	if (isM != std::string::npos) flag = flag | 1 << 2;

	if		(!(flag ^ (1 << 0)) && controller_index >= 0)
		__Decode_Gamepad(ih, str, controller_index);
	else if (!(flag ^ (1 << 1)))
		__Decode_Keyboard(ih, str);
	else if (!(flag ^ (1 << 2)))
		__Decode_Mouse(ih, str);
	else
	{
		Output_Handler::Error << "ERR Input_Handler::__Decode_Load : Bad keycode (" << str << ")\n";
		return nullptr;
	}
	return ih;
}



double Input_Handler::Check()
{
	if (!this)
	{
		//Output_Handler::Error << "ERR Input_Handler::Check : No Input Handler Initialized\n";
		return 0.0;
	}
	if (!Input_Function)
	{
		Output_Handler::Error << "ERR Input_Handler::Check : No Input Function supplied\n";
		return 0.0;
	}
	auto val = Input_Function(Input_Args);
	return val;
}



void Input_Handler::__Update()
{
	Keyboard_Handler::__Update();
	Mouse_Handler::__Update();
	Gamepad_Handler::__Update();
	Player::__Update();
}

#include "System.h"
void Input_Handler::__Events()
{
	Keyboard_Handler::__Events();
	Mouse_Handler::__Events();
	Gamepad_Handler::__Events();
	Player::__Events();
}


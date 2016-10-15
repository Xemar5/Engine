#include "Controls.h"

std::vector<std::vector<std::pair<double, int>>> Controls::_Gamepad_Hat;
std::map<unsigned, std::map<unsigned, int>> Controls::_Gamepad_Axes;
std::map<unsigned, std::map<unsigned, double>> Controls::_Gamepad_Buttons;
std::map<unsigned, double> Controls::_Keyboard_Buttons;
std::map<unsigned, double> Controls::_Mouse_Buttons;
int Controls::_new_Mouse_X = 0;
int Controls::_new_Mouse_Y = 0;

std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> Controls::_K_Up;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> Controls::_K_Down;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> Controls::_K_Click;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, double)>>> Controls::_K_Held;

std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> Controls::_G_Up;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> Controls::_G_Down;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> Controls::_G_Click;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned, double)>>> Controls::_G_Held;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> Controls::_G_Hat_Up;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> Controls::_G_Hat_Down;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> Controls::_G_Hat_Click;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned, double)>>> Controls::_G_Hat_Held;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned, int, int)>>> Controls::_G_Move;

std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> Controls::_M_Up;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> Controls::_M_Down;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> Controls::_M_Click;
std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, double)>>> Controls::_M_Held;
std::vector<std::pair<Entity*, std::function<void(Entity*, int, int, int, int)>>> Controls::_M_Move;

void Controls::Events()
{
	auto posK = _Keyboard_Buttons.end();
	auto posM = _Mouse_Buttons.end();
	auto posG = _Gamepad_Buttons[0].end();

	switch (System::Events.type)
	{
	case SDL_KEYDOWN:				for (auto cb : _K_Down) cb.second(cb.first, System::Events.key.keysym.sym);
									_Keyboard_Buttons[System::Events.key.keysym.sym] = 0;
									break;

	case SDL_KEYUP:				for (auto cb : _K_Up) cb.second(cb.first, System::Events.key.keysym.sym);
								posK = _Keyboard_Buttons.find(System::Events.key.keysym.sym);
								if (posK != _Keyboard_Buttons.end()) _Keyboard_Buttons.erase(posK);
								break;
		


	case SDL_MOUSEBUTTONDOWN:		for (auto cb : _M_Down) cb.second(cb.first, System::Events.button.button);
									_Mouse_Buttons[System::Events.button.button] = 0;
									break;

	case SDL_MOUSEBUTTONUP:		for (auto cb : _M_Up) cb.second(cb.first, System::Events.button.button);
								posM = _Mouse_Buttons.find(System::Events.button.button);
								if (posM != _Mouse_Buttons.end()) _Mouse_Buttons.erase(posM);
								break;

	case SDL_MOUSEMOTION:			_Mouse_Update(); break;



	case SDL_JOYBUTTONDOWN:		for (auto cb : _G_Up) cb.second(cb.first, System::Events.jbutton.which, System::Events.jbutton.button);
								_Gamepad_Buttons[System::Events.jbutton.which][System::Events.jbutton.button] = 0;
								break;

	case SDL_JOYBUTTONUP:			for (auto cb : _G_Down) cb.second(cb.first, System::Events.jbutton.which, System::Events.jbutton.button);
									if (_Gamepad_Buttons.find(System::Events.jbutton.which) == _Gamepad_Buttons.end()) break;
									posG = _Gamepad_Buttons[System::Events.jbutton.which].find(System::Events.jbutton.button);
									if (posG != _Gamepad_Buttons[System::Events.jbutton.which].end()) _Gamepad_Buttons[System::Events.jbutton.which].erase(posG);
									break;

	case SDL_JOYAXISMOTION:		_Gamepad_Axis_Update(); break;
	case SDL_JOYHATMOTION:		_Gamepad_Axis_Update(); break;
	default: break;
	}
}

void Controls::Update()
{
	for (auto p = _Keyboard_Buttons.begin(); p != _Keyboard_Buttons.end(); ++p)
		if (++p->second);
}

void Controls::_Mouse_Update()
{
	auto x = _new_Mouse_X;
	auto y = _new_Mouse_Y;
	SDL_GetMouseState(&_new_Mouse_X, &_new_Mouse_Y);
	for (auto cb : _M_Move) cb.second(cb.first, _new_Mouse_X, _new_Mouse_Y, x, y);
}

void Controls::_Gamepad_Axis_Update()
{
	//while (_Gamepad_Axes.size() <= System::Events.jaxis.which)
	//	_Gamepad_Axes.push_back({});
	//while (_Gamepad_Axes[System::Events.jaxis.which].size() <= System::Events.jaxis.axis)
	//	_Gamepad_Axes[System::Events.jaxis.which].push_back(0);

	for (auto cb : _G_Move) 
		cb.second
		(
			cb.first,
			System::Events.jaxis.which,
			System::Events.jaxis.axis,
			System::Events.jaxis.value,
			_Gamepad_Axes[System::Events.jaxis.which][System::Events.jaxis.axis]
		);

	_Gamepad_Axes[System::Events.jaxis.which][System::Events.jaxis.axis] = System::Events.jaxis.value;
}

void Controls::_Gamepad_Hat_Update()
{
	//while (_Gamepad_Hat.size() <= System::Events.jhat.which)
	//	_Gamepad_Hat.push_back({});
	//while (_Gamepad_Hat[System::Events.jhat.which].size() <= System::Events.jhat.hat)
	//	_Gamepad_Hat[System::Events.jhat.which].push_back({ 0,0 });


	//_Gamepad_Hat[System::Events.jhat.which][System::Events.jhat.hat].second = System::Events.jhat.value;
}

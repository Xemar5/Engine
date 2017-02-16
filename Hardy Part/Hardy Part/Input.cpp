#include "Input.h"
#include "System.h"
#include "State.h"

#include <SDL.h>
#include <string>



namespace controlls
{
	namespace impl
	{
		std::unordered_map<unsigned, std::unordered_map<unsigned, std::unordered_map<unsigned, Signal>>> input_map;

		bool Signal::EventResolve()
		{
			if (State::state_phase() != State::Phase::ObjectEvents && State::state_phase() != State::Phase::StateEvents) return true;
			if (_resolved) return false;
			return _resolved = true;
		}

		void Signal::_SetInput(unsigned device, unsigned action, unsigned index, unsigned time, double value)
		{
			auto& it = input_map[device][action][index];
			it.value = value;
			it.push_time = time;

			if (controlls::device.input->get_device() == device &&
				controlls::device.input->get_action() == action &&
				controlls::device.input->get_index() == index) return;

			controlls::device.input = controlls::GetInput<controlls::Input>(device, action, index);
			switch (device)
			{
			case 0: break;
			case 1: controlls::keyboard.input = controlls::device.input; break;
			case 2: controlls::mouse.input = controlls::device.input; break;
			default: controlls::gamepads[device - 3].input = controlls::device.input; break;
			}
		}


		void Signal::Update()
		{
			for (auto& d : input_map)
				for (auto& a : d.second)
					for (auto& i : a.second)
					{
						i.second.last_value = i.second.value;
						i.second._resolved = false;
					}
		}

		void Signal::Events()
		{
			switch (System::Events.type)
			{
			case SDL_KEYDOWN:		if (!input_map[1][1][System::Events.key.keysym.sym].push_time)
				_SetInput(1, 1, System::Events.key.keysym.sym, System::Events.key.timestamp, 1); break;
			case SDL_KEYUP:				_SetInput(1, 1, System::Events.key.keysym.sym, 0, 0); break;

			case SDL_MOUSEBUTTONDOWN:	_SetInput(2, 1, System::Events.button.button, System::Events.button.timestamp, 1); break;
			case SDL_MOUSEBUTTONUP:		_SetInput(2, 1, System::Events.button.button, 0, 0); break;
			case SDL_MOUSEMOTION:	if (System::Events.motion.xrel)
			{
				_SetInput(2, 2, 0, System::Events.motion.timestamp, System::Events.motion.x);
				input_map[2][2][2].push_time = System::Events.motion.timestamp;
				input_map[2][2][2].value = (double)System::Events.motion.xrel;
			}
									if (System::Events.motion.yrel)
									{
										_SetInput(2, 2, 1, System::Events.motion.timestamp, System::Events.motion.y);
										input_map[2][2][3].push_time = System::Events.motion.timestamp;
										input_map[2][2][3].value = (double)System::Events.motion.xrel;
									}
									break;

			case SDL_CONTROLLERBUTTONDOWN:		if (gamepads[System::Events.cbutton.which].is_gamecontroller())_SetInput(System::Events.cbutton.which + 3, 1, System::Events.cbutton.button, System::Events.cbutton.timestamp, 1); break;
			case SDL_JOYBUTTONDOWN:				if (!gamepads[System::Events.jbutton.which].is_gamecontroller())_SetInput(System::Events.jbutton.which + 3, 1, System::Events.jbutton.button, System::Events.jbutton.timestamp, 1); break;
			case SDL_CONTROLLERBUTTONUP:		if (gamepads[System::Events.cbutton.which].is_gamecontroller())_SetInput(System::Events.cbutton.which + 3, 1, System::Events.cbutton.button, 0, 0); break;
			case SDL_JOYBUTTONUP:				if (!gamepads[System::Events.jbutton.which].is_gamecontroller())_SetInput(System::Events.jbutton.which + 3, 1, System::Events.jbutton.button, 0, 0); break;
			case SDL_CONTROLLERAXISMOTION:		if (gamepads[System::Events.caxis.which].is_gamecontroller())_SetInput(System::Events.caxis.which + 3, 2, System::Events.caxis.axis, System::Events.caxis.value ? System::Events.caxis.timestamp : 0, System::Events.caxis.value); break;
			case SDL_JOYAXISMOTION:				if (!gamepads[System::Events.jaxis.which].is_gamecontroller())_SetInput(System::Events.jaxis.which + 3, 2, System::Events.jaxis.axis, System::Events.jaxis.value ? System::Events.jaxis.timestamp : 0, System::Events.jaxis.value); break;
			case SDL_JOYHATMOTION:				if (!gamepads[System::Events.jhat.which].is_gamecontroller())_SetInput(System::Events.jhat.which + 3, 3, System::Events.jhat.hat, System::Events.jhat.value ? System::Events.jhat.timestamp : 0, System::Events.jhat.value); break;
			//case SDL_CONTROLLERDEVICEADDED:
			case SDL_JOYDEVICEADDED:			Gamepad::_AddJoystick(System::Events.jdevice.which); break;
			//case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_JOYDEVICEREMOVED:			Gamepad::_RemoveJoystick(System::Events.jdevice.which); break;
			default: break;
			}

		}



		bool Hat::pushed()
		{
			auto& it = input_map[_device][3][_index];
			unsigned last = (unsigned)it.last_value;
			unsigned val = (unsigned)it.value;
			if (_modifier == (unsigned)Directions::None) return ~last & val ? it.EventResolve() : false;
			else return _modifier == (~last & val) ? it.EventResolve() : false;
		}

		bool Hat::released()
		{
			auto& it = input_map[_device][3][_index];
			unsigned last = (unsigned)it.last_value;
			unsigned val = (unsigned)it.value;
			if (_modifier == (unsigned)Directions::None) return last & ~val ? it.EventResolve() : false;
			else return _modifier == (last & ~val) ? it.EventResolve() : false;
		}

		bool Mouse::ContainsMouse(std::shared_ptr<Entity> ent)
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
		
			SDL_Point p;
			SDL_GetMouseState(&p.x, &p.y);
			double px = (double)p.x + Camera::Main->X;
			double py = (double)p.y + Camera::Main->Y;
		
			//double px = Mouse::Get[Input::Change(IT_MOUSE_AXIS, MA_X)].Held();
			//double py = Mouse::Get[Input::Change(IT_MOUSE_AXIS, MA_Y)].Held();
			auto sp = ent->texture;
			auto scale = ent->RootScale();
			auto pos = ent->RootPos();
			double offx = sp->Starting_Point().x * scale / Camera::Main->scale;
			double offy = sp->Starting_Point().y * scale / Camera::Main->scale;
			return (
				px >= pos[0] - offx &&
				px <= pos[0] - offx + ent->hitbox().first &&
				py >= pos[1] - offy &&
				py <= pos[1] - offy + ent->hitbox().second
				);
		}

		void Gamepad::_AddJoystick(unsigned id)
		{
			//auto it = gamepads.map.find(id);
			//if (it != gamepads.map.end() && (it->second._joystick || it->second._controller)) return;

			if (SDL_IsGameController(id))
			{
				auto controller = SDL_GameControllerOpen(id);
				auto new_id = (unsigned)SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
				auto& g = gamepads.map.insert({ new_id,{ new_id } }).first->second;
				g._controller = controller;
				g._name = SDL_GameControllerName(controller);
				g._name.erase(std::remove_if(g._name.begin(), g._name.end(), [](int i)->bool { return i < 0 ? true : false; }), g._name.end());
				gamepads.last_connected = new_id;
			}
			else
			{
				auto joystick = SDL_JoystickOpen(id);
				auto new_id = (unsigned)SDL_JoystickInstanceID(joystick);
				auto& g = gamepads.map.insert({ new_id,{ new_id } }).first->second;
				g._joystick = joystick;
				g._name = SDL_JoystickName(joystick);
				g._name.erase(std::remove_if(g._name.begin(), g._name.end(), [](int i)->bool { return i < 0 ? true : false; }), g._name.end());
				gamepads.last_connected = new_id;
			}

		}

		void Gamepad::_RemoveJoystick(unsigned id)
		{
			auto it = gamepads.map.find(id);
			if (it == gamepads.map.end() || (!it->second._joystick && !it->second._controller)) return;
			auto& gp = it->second;
			if (gp._joystick)
			{
				SDL_JoystickClose(gp._joystick);
				gp._joystick = nullptr;
			}
			if (gp._controller)
			{
				SDL_GameControllerClose(gp._controller);
				gp._controller = nullptr;
			}
		}


		std::string Input::get_action_name()
		{
			switch (get_action())
			{
			case 1: return "Button";
			case 2: return get_device() == 2 ? get_index() == 0 ? "Horizontal Axis" : "Vetrical Axis" : "Axis";
			case 3: return "Hat";
			default: return "Unknown";
			}
			return std::string();
		}

		bool MouseAxis::pushed()
		{
			int val = get_index() == 0 ? Screen::Window_Size().first : Screen::Window_Size().second;
			return abs(raw_value() - val / 2) > val / 4;
		}

} //namespace impl

	impl::Device device{ 0 };
	impl::Keyboard keyboard;
	impl::Mouse mouse;
	impl::GamepadMap gamepads;

} //namespace controlls


#pragma once
#include "State.h"

class DeviceConfig_State : public State
{
	class Background : public Entity
	{
		void Create()
		{
			Sprite::Load(*this, "Resources/DeviceAdded_Resources/Background.png", 1, 1, -1, -1, 1, 1);
			scale = 2000;
			State::AddChild(1, *this);
		}
	};

	struct ProgressBar : public Entity
	{
		void Create()
		{
			State::AddChild(2, *this);
			Shape::Load(*this, [](std::shared_ptr<Entity> ent, std::shared_ptr<Shape> texture, double parent_x, double parent_y, double parent_scale, double parent_rotation)->bool
			{
				int w = (int)(boost::any_cast<double>(texture->values[0]) * 300.);
				SDL_Rect r{ ((int)Screen::Window_Size().first - w) / 2, (int)Screen::Window_Size().second * 3 / 4, w, 10 };
				SDL_SetRenderDrawColor(Screen::Renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(Screen::Renderer, &r);
				return true;
			});
			Shape::SetValues(*this, 0.);
		}
		void SetVal(double val)
		{
			std::dynamic_pointer_cast<Shape>(texture)->values[0] = val;
		}
	};
	std::shared_ptr<ProgressBar> progress_bar;

	struct ActionName : public Textfield
	{
		void Create()
		{
			Textfield::SetText(*this, " ", "imgs/slkscr.ttf", 48);
			State::AddChild(2, *this);
			X = Screen::Window_Size().first - 20;
			Y = Screen::Window_Size().second / 4;
			this->texture->Set_Starting_Pos(1, -1);
		}
		void ChangeText(std::string action_name)
		{
			Textfield::SetText(*this, action_name, "imgs/slkscr.ttf", (Uint32)82);
		}
	};
	std::shared_ptr<ActionName> action_name;

	struct GamepadName : public Textfield
	{
		GamepadName(std::string name) : name(name) {}
		std::string name;
		void Create()
		{
			Textfield::SetText(*this, name, "imgs/slkscr.ttf", 18);
			State::AddChild(2, *this);
			X = 20;
			Y = 20;
			this->texture->Set_Starting_Pos(-1, -1);
		}
	};

	struct StateNumbers : public Textfield
	{
		StateNumbers(unsigned size) : size(size) {}
		unsigned size;
		void Create()
		{
			Textfield::SetText(*this, "[0 / " + std::to_string(size) + "]", "imgs/slkscr.ttf", 18);
			State::AddChild(2, *this);
			X = Screen::Window_Size().first - 20;
			Y = 20;
			this->texture->Set_Starting_Pos(1, -1);
		}
		void ChangeState(unsigned new_state)
		{
			Textfield::SetText(*this, "[" + std::to_string(new_state) + " / " + std::to_string(size) + "]", "imgs/slkscr.ttf", 18);
		}
	};
	std::shared_ptr<StateNumbers> state_numbers;


	//*** The time input needs to be pushed to be set
	int state_progress_timer = 20;
	//*** Index of the action that is being processed
	int state_index = 0;
	//*** The progress of a currently processed action
	int state_progress = 0;
	//*** The input selected for current action
	controlls::Input selected_input;
	//*** The index of the device being connected
	unsigned device;
	//*** The name of the device
	std::string device_name;
	//*** Currently edited mapping
	std::shared_ptr<controlls::Mapping> mapping = nullptr;
	//*** Contains names and descriptions of all device actions
	std::vector<std::pair<std::string, std::string>> actions =
	{
		{ "Move Up", "la_up" },
		{ "Move Down", "la_down" },
		{ "Move Left", "la_left" },
		{ "Move Right", "la_right" },
		{ "Aim Up", "ra_up" },
		{ "Aim Down", "ra_down" },
		{ "Aim Left", "ra_left" },
		{ "Aim Right", "ra_right" },
		{ "Action", "action" },
		{ "Utility", "utility" },
		{ "Start", "start" }
	};
	//*** Iterates through supplied map in search of all actions from vector above
	bool _CheckActions(std::map<std::string, std::tuple<unsigned, unsigned, unsigned>> map)
	{
		bool found;
		for (auto action = actions.begin(); action != actions.end(); ++action)
		{
			found = false;
			for (auto saved = map.begin(); saved != map.end(); ++saved)
			{
				if (saved->first == action->second)
				{
					found = true;
					break;
				}
			}
			if (!found) return false;
		}
		return true;
	}

public:
	DeviceConfig_State(unsigned device) : device(device) {}

	void Create()
	{
		device_name = device < 3 ? "Keyboard" : controlls::gamepads[device - 3].name();

		for (auto map = controlls::Mapping::Maps.begin(); map != controlls::Mapping::Maps.end(); ++map)
		{
			if (map->first == device_name)
			{
				if (_CheckActions(map->second))
				{
					State::Remove();
					return;
				}
			}
		}
		if (!mapping) mapping = std::make_shared<controlls::Mapping>();

		State::GetLayer(2)->scale = 0.5;
		State::GetLayer(2)->X = Camera::Main->X;
		State::GetLayer(2)->Y = Camera::Main->Y;


		Object::Make<Background>();
		action_name = Object::Make<ActionName>();
		action_name->ChangeText(actions[state_index].first);
		progress_bar = Object::Make<ProgressBar>();
		state_numbers = Object::Make<StateNumbers>(actions.size());
		Object::Make<GamepadName>(device_name);

	}
	void Update()
	{
		if (selected_input && state_progress < state_progress_timer)
		{
			++state_progress;
			progress_bar->SetVal((double)(state_progress % state_progress_timer) / (double)state_progress_timer);
			if (state_progress == state_progress_timer)
			{
				//std::cout << "[SET]";
				(*mapping).operator<<({ actions[state_index].second, {selected_input->get_action(), selected_input->get_index(), selected_input->get_modifier()} });

				++state_index;
				//*** Keyboard Offset
				while (device < 3 && state_index >= 4 && state_index <= 7)
				{
					if (state_index == 4 || state_index == 5)
						(*mapping).operator<<({ actions[state_index].second,{ 2, 1, 0 } });
					if (state_index == 6 || state_index == 7)
						(*mapping).operator<<({ actions[state_index].second,{ 2, 0, 0 } });
					++state_index;
				}

				state_numbers->ChangeState(state_index);
				if (state_index == actions.size())
				{
					//std::cout << "Input [" << selected_input->get_action_name() << ", " << std::to_string(selected_input->get_index()) << "] Set\n";
					mapping->Save(device_name);
					State::Remove();
				}
				else action_name->ChangeText(actions[state_index].first);
			}
		}
	}
	void Events()
	{
		if (selected_input && selected_input->released())
		{
			//std::cout << "Selected Input Released\n";
			//if (state_progress == state_progress_timer)
			//{
			//	std::cout << "Input [" << selected_input->get_action_name() << ", " << std::to_string(selected_input->get_index()) << "] Set\n";
			//}
			selected_input = nullptr;
			state_progress = 0;
			progress_bar->SetVal((double)(state_progress % state_progress_timer) / (double)state_progress_timer);
		}

		if (!selected_input &&
			controlls::device.input->get_device() == device &&
			controlls::device.input->pushed())
		{
			//std::cout << "New Input Selected\n";
			selected_input = controlls::StoreInput(controlls::device.input);
		}
	}
};
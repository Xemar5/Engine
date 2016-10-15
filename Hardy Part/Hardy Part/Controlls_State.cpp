#include <string>
#include "Controlls_State.h"
#include "Sprite.h"
#include "Device.h"
#include "Textfield.h"

Textfield* selectedDevice = nullptr;
std::string actionName = "";
SDL_Point lastMousePos;

void selectDevice(Textfield* tf)
{
	if (selectedDevice) Textfield::SetText(selectedDevice, selectedDevice->Text(), "imgs/clacon.ttf", 32, Textfield::Color(0xffffff00));
	selectedDevice = tf;
	Textfield::SetText(selectedDevice, selectedDevice->Text(), "imgs/clacon.ttf", 32, Textfield::Color(0x44444400));
	auto& d = Device::Get(selectedDevice->Text());
	for (auto i : Entity::Registered())
		if (i.first.find("action") != std::string::npos)
		{
			auto k = i.second->As<Textfield>()->Text();
			auto s = d.Bindings[k.c_str()].KeyName();
			auto t = Entity::Registered()[k]->As<Textfield>()->SetText(s, "imgs/clacon.ttf", 32, Textfield::Color(s == "[Unknown Input]" ? 0xff666600 : 0xffffff00));
			t->X = Screen::Get_Screen_Size().first / 2 + t->TextWidth() / 2 + 20;
		}
}


class Controlls_State_Popup : public State
{
	void Create() override;
	void Update() override;
	void Events() override;
};
void Controlls_State_Popup::Create()
{
	auto e = State::Add_Entity<Textfield>()->As<Textfield>();
	e->SetText("Select", "imgs/clacon.ttf", 32, Textfield::Color(0x24ef49ff));
	e->Y = 20;
	e->X = Screen::Get_Screen_Size().first / 2;
}
void Controlls_State_Popup::Update()
{

}

void selectAndConfirm()
{
	SDL_WarpMouseInWindow(Screen::Window, lastMousePos.x, lastMousePos.y);
	State::Exit_Layer();
	selectDevice(selectedDevice);
}
void Controlls_State_Popup::Events()
{
	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_F1)].Up() &&
		!Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_F1)].Click())
	{
		selectAndConfirm();
	}
	else if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Up() &&
		!Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Click())
	{
		Device::Get(selectedDevice->Text()).Bindings << actionName + Input::Set(IT_UNDEFINED, IK_UNDEFINED);
		selectAndConfirm();
	}
	else if (&Device::GetCurrent() == &Device::Get(selectedDevice->Text()) && System::Events.type == SDL_MOUSEMOTION)
	{
		auto p = Screen::Get_Window_Size();
		if (abs((Sint32)p.first / 2 - System::Events.motion.x) > 100)
		{
			Device::Get(selectedDevice->Text()).Bindings << actionName + Input::Set(IT_MOUSE_AXIS, MA_X);
			selectAndConfirm();
		}
		else if (abs((Sint32)p.second / 2 - System::Events.motion.y) > 100)
		{
			Device::Get(selectedDevice->Text()).Bindings << actionName + Input::Set(IT_MOUSE_AXIS, MA_Y);
			selectAndConfirm();
		}
	}
	else if(&Device::GetCurrent() == &Device::Get(selectedDevice->Text()) && Device::GetCurrent()[Input::Set(~IT_MOUSE_AXIS, IK_ANY)].Up())
		//if (Device::GetCurrent()[Input::Set(IT_ANY, IK_ANY)].Up())
	{
		auto ci = Device::GetCurrent().CurrentInput();
		if (!ci) return;
		Device::Get(selectedDevice->Text()).Bindings << actionName + Input::Set(ci->Type(), ci->Key(), ci->ControllerID(), ci->Variant(), IS_HELD);
		selectAndConfirm();
	}
}












void Controlls_State::Create()
{
	actionName = "";
	selectedDevice = nullptr;
	std::vector<std::string> inputs = 
	{
		"laup",
		"ladown",
		"laleft",
		"laright",
		"raup",
		"radown",
		"raleft",
		"raright",

		"a",
		"b",

		"x",
		"y",
		"r1",
		"l1",

		"start"
	};
	int ind = 0;
	int yDelta = 13;
	int yPos = 100;
	int xPos = Screen::Get_Screen_Size().first / 2;

	auto save_btn = State::Add_Entity<Textfield>(0)->As<Textfield>();
	Entity::Register(save_btn, "save_btn");
	save_btn->SetText("Save", "imgs/clacon.ttf", 32);
	save_btn->X = save_btn->TextWidth() / 2 + 20;
	save_btn->Y = save_btn->TextHeight() / 2 + 20;


	for (auto i : inputs)
	{
		auto action = State::Add_Entity<Textfield>(0)->As<Textfield>();
		auto input = State::Add_Entity<Textfield>(0)->As<Textfield>();
		Entity::Register(action, "action" + std::to_string(ind));
		Entity::Register(input, i);
		action->SetText(i, "imgs/clacon.ttf", 32);
		input->SetText("x", "imgs/clacon.ttf", 32);
		action->X = xPos - action->TextWidth() / 2 - 5;
		input->X = xPos + input->TextWidth() / 2 + 20;
		action->Y = yPos;
		input->Y = yPos;
		yPos += yDelta;
		++ind;
	}
	ind = 0;
	yPos = 100;
	for (auto d : Gamepad::All())
	{
		auto tf = State::Add_Entity<Textfield>(0)->As<Textfield>();
		Entity::Register(tf, "device" + std::to_string(ind));
		tf->SetText(d->Name(), "imgs/clacon.ttf", 32);
		tf->X = 20 + tf->TextWidth() / 2;
		tf->Y = yPos;
		yPos += yDelta;
		++ind;
	}

	selectDevice(Entity::Get("device0")->As<Textfield>());
	//auto cs1 = State::Add_Entity(1);
	//Sprite::Load(cs1.get(), "imgs/Character_Selection.png", 80, 48, 0, 0, 0, 0);
	//cs1->X = Screen::Get_Screen_Size().first / 2;
	//cs1->Y = Screen::Get_Screen_Size().second / 2;
	////cs1->Get_Sprite()->Scale = 1.5;

	//auto tf = State::Add_Entity<Textfield>(0);
	//dynamic_cast<Textfield*>(tf.get())->Set("WHAT IS WRONG WITH ME, why is this text so long wtf", "imgs/slkscr.ttf", 32, Textfield::Color(0xffffffff), 300);
	//tf->X = 100;
	//tf->Y = 100;

}

void Controlls_State::Update()
{

}




void Controlls_State::Events()
{
	if (System::Events.type == SDL_JOYDEVICEADDED || System::Events.type == SDL_JOYDEVICEREMOVED) State::New<Controlls_State>();
	else if (Mouse::Get[Input::Set(IT_MOUSE_BUTTON, SDL_BUTTON_LEFT)].Up())
	{
		if (Mouse::Contains_Mouse(Entity::Get("save_btn")))
		{
			for (auto d : Device::All())
				d->Bindings.Save(d->Name());
		}
		for (auto i = Entity::__Registered.begin(); i != Entity::__Registered.end(); ++i)
		{
			auto e = i->first.find("device");
			if (e == std::string::npos)
			{
				e = i->first.find("action");
				if (e == std::string::npos) continue;
				else
					if (Mouse::Contains_Mouse(i->second))
					{
						SDL_GetMouseState(&lastMousePos.x, &lastMousePos.y);
						actionName = i->second->As<Textfield>()->Text();
						State::New_Layer<Controlls_State_Popup>();
						SDL_WarpMouseInWindow(Screen::Window, Screen::Get_Window_Size().first / 2, Screen::Get_Window_Size().second / 2);
					}
			}
			else
				if (Mouse::Contains_Mouse(i->second))
					selectDevice(i->second->As<Textfield>());
		}
	}
	else if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Up()) State::New<Menu_Menu>();
	else if (Device::GetCurrent()["back"].Up()) State::New<Menu_Menu>();
}
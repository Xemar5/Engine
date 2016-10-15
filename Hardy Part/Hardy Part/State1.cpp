#include "State1.h"
#include "Device.h"
#include "Generic.h"
void State1::Create()
{
}

unsigned flaggg = 0;
void State1::Update()
{
	if (Get_Entities().size())
	{
		Ent(Get_Entities().size() - 1)->X = Mouse::Get[Input::Set(IT_MOUSE_AXIS, MA_X, IS_ANY)].Down();
		Ent(Get_Entities().size() - 1)->Y = Mouse::Get[Input::Set(IT_MOUSE_AXIS, MA_Y, IS_ANY)].Down();
	}
}

void State1::Events()
{
	if (Mouse::Get[Input::Set(IT_MOUSE_BUTTON, SDL_BUTTON_LEFT, IS_PUSHED)].Down())
	{
		auto e1 = State::Add_Entity<Entity>(0);
		Generic::Load({ { flaggg++ % 6 } }, e1.get(), "imgs/nerk-sheet.png", 144, 24, 0, 0, 24, 24);
	}

	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_SPACE, IS_PUSHED)].Down())
		State::New<State2>(Get_Entities());
}

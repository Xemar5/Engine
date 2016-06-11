#include "Controlls_State.h"
#include "Sprite.h"
#include "Device.h"
#include "Textfield.h"

void Controlls_State::Create()
{
	auto cs1 = State::Add_Entity(1);
	Sprite::Create(cs1.get(), Texture::Load("imgs/Character_Selection.png", 80, 48, 0, 0, 0, 0));
	cs1->X = Screen::Get_Screen_Size().first / 2;
	cs1->Y = Screen::Get_Screen_Size().second / 2;
	//cs1->Get_Sprite()->Scale = 1.5;

	auto tf = State::Add_Entity<Textfield>(0);
	dynamic_cast<Textfield*>(tf.get())->Set("WHAT IS WRONG WITH ME", "imgs/slkscr.ttf", 32);
	tf->X = 100;
	tf->Y = 100;
}

void Controlls_State::Update()
{

}

void Controlls_State::Events()
{
	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Up()) State::New<Menu_Menu>();

}
#include "Menu_State.h"
#include "Entity.h"
#include "Keyboard_Handler.h"
#include "Main_State.h"

#include "Sprite.h"
#include "Texture.h"
#include "Animation.h"

void Menu_Menu::Create()
{
	auto* bg = State::Add_Entity<Entity>(0);
	Sprite::Create(bg, Texture::Load("imgs/main_menu-sheet.png", 2800, 2100, 400, 300, 0, 0));
	Animation::Add(bg, "idle", "24-47x4", true);
	Animation::Add(bg, "start", "0-23x4", false);
	Animation::Play(bg, "start");
	bg->X = Screen::Width / 2;
	bg->Y = Screen::Height / 2;
}
void Menu_Menu::Update()
{
	State::Update();
}
void Menu_Menu::Events()
{
	if (Keyboard_Handler::Key_Up({ SDLK_SPACE }))
		State::New<Main_Menu>();
	if (Keyboard_Handler::Key_Up({ SDLK_RETURN }))
		Screen::Change_Window_State();
	State::Events();
}


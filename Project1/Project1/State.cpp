#include "State.h"
#include "Entity.h"
#include "Screen.h"
#include "Sprite_Handler.h"

std::vector<std::shared_ptr<State>> State::Built;
std::vector<unsigned> State::Deleted;


void State::Update()
{
	for (auto layer : Layers)
		if (layer->Update_Entities)
			for (auto ent : layer->Entities)
			{
				ent->Update();
				Screen::Add(ent->Get_Sprite_Handler(), ent->X, ent->Y);
			}
	Screen::Draw();
}
void State::Events()
{
	for (auto layer : Layers)
		if (layer->Events_Entities)
			for (auto ent : layer->Entities)
				ent->Events();
}




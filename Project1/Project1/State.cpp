#include "State.h"
#include "Entity.h"
#include "Screen.h"
#include "Sprite.h"
#include "Animation.h"

std::vector<std::shared_ptr<State>> State::Built;
std::vector<unsigned> State::Deleted;


void State::Update()
{
	for (auto layer : Layers)
		if (layer->Update_Entities)
			for (auto ent : layer->Entities)
			{
				if (Animation::Next_Frame(ent.get()) != -1)
					Animation::Set_Frame(ent.get(), ent->Get_Sprite()->Get_Current_Frame());
				ent->Update();
				if (!ent->Get_Sprite()->Get_Current_Animation()) Animation::Play(ent.get());
				Screen::Add(ent->Get_Sprite(), ent->X, ent->Y);
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




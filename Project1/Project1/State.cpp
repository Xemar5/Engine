#include "State.h"
#include "Entity.h"
#include "Screen.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Tileset.h"

std::vector<std::shared_ptr<State>> State::Built;
std::vector<unsigned> State::Deleted;


void State::Update()
{
	if (Tile_Set) Screen::Add(Tile_Set.get());
	for (auto layer : Layers)
		if (layer->Update_Entities)
			for (auto ent : layer->Entities)
			{
				if (Animation::Next_Frame(ent.get()) != -1)
					Animation::Set_Frame(ent.get(), ent->Get_Sprite()->Get_Current_Frame());
				
				ent->Update();

				if (ent->Get_Movement())
					if (Movement::__Resolve_Movement(ent.get()))
						Animation::Play(ent.get(), "move");
					else Animation::Terminate(ent.get(), "move");

				if (!ent->Get_Sprite()->Get_Current_Animation()) Animation::Play(ent.get());
				Screen::Add(ent.get());
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




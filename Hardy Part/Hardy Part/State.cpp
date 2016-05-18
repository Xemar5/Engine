#include "State.h"
#include "Entity.h"
#include "Screen.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Tileset.h"
#include "Output_Handler.h"

std::vector<std::shared_ptr<State>> State::Built;
std::vector<unsigned> State::Deleted;


void State::Update()
{
	//for (auto tileset : __Tilesets)
	//	Screen::Add(tileset.get());
	for (auto layer : Layers)
		if (layer->Update_Entities)
			for (auto ent : layer->Entities)
			{
				if (ent->Get_Sprite())
					if (Animation::Next_Frame(ent.get()) != -1)
						Animation::Set_Frame(ent.get(), ent->Get_Sprite()->Get_Current_Frame());

				ent->Update();

				if (ent->Get_Movement())
				{
					if (Movement::__Resolve_Movement(ent.get()))
						Animation::Play(ent.get(), "move");
					else Animation::Terminate(ent.get(), "move");
				}

				if (ent->Get_Sprite())
					if (!ent->Get_Sprite()->Get_Current_Animation()) Animation::Play(ent.get());
				//Screen::Add(ent.get());
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

bool State::Set_Entity_Layer(State * state, Entity * entity, unsigned new_layer)
{
	if (!state)
	{
		Output_Handler::Error << "ERR State::Set_Entity_Layer : No State supplied\n";
		return false;
	}
	if (!entity)
	{
		Output_Handler::Error << "ERR State::Set_Entity_Layer : No Entity supplied\n";
		return false;
	}
	for (unsigned lay = 0; lay < state->Layers.size(); ++lay)
		for (unsigned ent = 0; ent < state->Layers[lay]->Entities.size(); ++ent)
			if (state->Layers[lay]->Entities[ent].get() == entity)
			{
				state->Add_Entity(entity, new_layer);
				state->Layers[lay]->Entities.erase(state->Layers[lay]->Entities.begin() + ent);
				Screen::Add((*state)[new_layer].Entities.back(), new_layer);
				entity->__Layer = new_layer;
				return true;
			}
	Output_Handler::Error << "ERR State::Set_Entity_Layer : Couldn't find entity on any layer in given state (maybe use State::Add_Entity instead)\n";
	return false;
}

//std::shared_ptr<Tileset> State::Add_Tileset(std::shared_ptr<Texture> texture, unsigned layer, std::pair<int, int> pos, std::vector<std::vector<unsigned>> map)
//{
//	if (!this)
//	{
//		Output_Handler::Error << "ERR State::Add_Tileset : No this State\n";
//		return nullptr;
//	}
//	if (!texture)
//	{
//		Output_Handler::Error << "ERR State::Add_Tileset : No texture supplied\n";
//		return nullptr;
//	}
//	while (Layers.size() <= layer) Layers.emplace_back(std::make_shared<Layer>());
//	Layers[layer]->Tilesets.push_back(Tileset::Set(texture, pos, map));
//	Screen::Add(Layers[layer]->Tilesets.back(), layer);
//	return Layers[layer]->Tilesets.back();
//}

//std::vector<std::shared_ptr<Tileset>> State::Get_Tilesets()
//{
//	std::vector<std::shared_ptr<Tileset>> v;
//	for (auto lay : Layers)
//		for (auto ts : lay->Tilesets)
//			v.push_back(ts);
//	return v;
//}

std::vector<Tileset*> State::Get_Tilesets()
{
	std::vector<Tileset*> v;
	for (auto lr : Layers)
		for (auto ent : lr->Entities)
			if (auto ts = dynamic_cast<Tileset*>(ent.get()))
				v.push_back(ts);
	return v;
}

std::vector<Entity*> State::Get_Entities()
{
	std::vector<Entity*> v;
	for (auto lr : Layers)
		for (auto ent : lr->Entities)
		{
			if (dynamic_cast<Tileset*>(ent.get())) continue;
			v.push_back(ent.get());
		}
	return v;
}

Layer & State::operator[](unsigned layer)
{
	if (layer >= Layers.size())
	{
		Output_Handler::Output << "MSG State::operator[] : State has no layer with given index; creating layer with given index and belove\n";
		while (Layers.size() <= layer) Layers.emplace_back(std::make_shared<Layer>());
	}
	return *Layers[layer].get();
}

//Tileset * Layer::operator()(unsigned tileset)
//{
//	if (tileset >= Tilesets.size())
//	{
//		Output_Handler::Error << "ERR Layer::operator() : Layer has no tileset with given index\n";
//		return nullptr;
//	}
//	return Tilesets[tileset].get();
//}

Entity * Layer::operator[](unsigned ent)
{
	if (ent >= Entities.size())
	{
		Output_Handler::Error << "ERR Layer::operator[] : Layer has no entity with given index\n";
		return nullptr;
	}
	return Entities[ent].get();
}

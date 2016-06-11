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
	for (auto ent : __Entities)
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
	for (auto ent : __Entities)
		ent->Events();
}

bool State::Remove_Entity(Entity * ent)
{
	if (!ent)
	{
		Output_Handler::Output << "MSG State::Remove_Entity : No entity supplied\n";
		return false;
	}
	for (auto it = __Entities.begin(); it != __Entities.end(); ++it)
		if (ent == it->get())
		{
			__Entities.erase(it);
			return true;
		}
	Output_Handler::Output << "MSG State::Remove_Entity : entity not found\n";
	return false;
}

bool State::Change_Entity_Layer(Entity* entity, unsigned new_layer)
{
	if (!entity)
	{
		Output_Handler::Error << "ERR State::Set_Entity_Layer : No Entity supplied\n";
		return false;
	}
	entity->__Layer = new_layer;
	Screen::Change_Layer(entity);
	return true;
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

std::vector<Entity*> State::Get_Entities()
{
	std::vector<Entity*> v(__Entities.size());
	for (unsigned i = 0; i < __Entities.size(); ++i)
		v[i] = __Entities[i].get();
	return v;
}

Entity* State::Ent(unsigned ent)
{
	if (ent >= __Entities.size())
	{
		Output_Handler::Output << "MSG State::operator[] : State has no layer with given index; creating layer with given index and belove\n";
		return nullptr;
	}
	return __Entities[ent].get();
}


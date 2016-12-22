#include "State.h"
#include "Entity.h"
#include "Screen.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Generic.h"
#include "Output_Handler.h"
#include "Texture.h"

std::vector<std::shared_ptr<State>> State::Built;
std::vector<unsigned> State::Deleted;


void State::Update()
{
	for (auto ent : ent::All)
	{
		auto sp = std::dynamic_pointer_cast<Sprite>(ent->texture);
		if (sp)
			if (sp->Current_Animation())
				sp->Current_Animation()->Next_Frame();

		ent->Update();

		if (ent->movement && sp)
		{
			if (Movement::__Resolve_Movement(ent))
				sp->operator[]("move").Play();
			else if(sp->Current_Animation())
				sp->Current_Animation()->Terminate();
		}

		if (sp && !sp->Current_Animation()) sp->operator[]("idle").Play();
	}
	Screen::Draw();
}
void State::Events()
{
	for (auto ent : ent::All)
		ent->Events();
}

//bool State::Remove_Entity(Entity * ent)
//{
//	if (!ent)
//	{
//		Output_Handler::Output << "MSG State::Remove_Entity : No entity supplied\n";
//		return false;
//	}
//	for (auto it = __Entities.begin(); it != __Entities.end(); ++it)
//		if (ent == it->get() && it->use_count() == 2)
//		{
//			for (auto& e = Screen::__Entities.begin(); e != Screen::__Entities.end(); ++e)
//				if (e->get() == ent)
//				{
//					Screen::__Entities.erase(e);
//					break;
//				}
//			Entity::Destroy(it->get());
//			__Entities.erase(it);
//			return true;
//		}
//	Output_Handler::Output << "MSG State::Remove_Entity : Entity not found\n";
//	return false;
//}

bool State::Change_Entity_Layer(ent::Entity<> entity, unsigned new_layer)
{
	if (!entity)
	{
		Output_Handler::Error << "ERR State::Set_Entity_Layer : No Entity supplied\n";
		return false;
	}
	entity->layer = new_layer;
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


//std::vector<ent::Entity<>> State::Get_Entities()
//{
//	return ent::All;
//}

//ent::Entity<> State::Ent(unsigned ent)
//{
//	if (ent >= ent::All.size()) return nullptr;
//	return __Entities[ent];
//}

//bool State::Remove_Entity(ent::Entity<> ent)
//{
//	for (auto it = __Entities.begin(); it != __Entities.end(); ++it)
//		if (*it == ent)
//		{
//			__Entities.erase(it);
//			break;
//		}
//	for(auto& l : Screen::__Entities)
//		for (auto it = l.begin(); it != l.end(); ++it)
//			if (*it == ent)
//			{
//				l.erase(it);
//				break;
//			}
//	for (auto it = Player::__Players.begin(); it != Player::__Players.end(); ++it)
//		if ((*it)->__Entity == ent)
//			(*it)->__Entity = nullptr;
//	return true;
//}


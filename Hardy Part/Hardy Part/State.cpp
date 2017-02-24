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
std::vector<unsigned> State::Created;
State::Phase State::_state_phase = State::Phase::SystemReserved;
std::shared_ptr<State> State::_CurrentState = nullptr;



void State::Update()
{
	for (auto ent : _layer_vector)
		__Update(ent.second);
	Screen::Draw();
}
void State::Events()
{
	for (auto ent : _layer_vector)
		__Events(ent.second);
}



std::shared_ptr<State> State::CurrentState()
{
	return _CurrentState;
}

void State::__Update(std::shared_ptr<Object> e)
{
	if (auto c = std::dynamic_pointer_cast<Container>(e))
	{
		for(auto child : c->children)
			__Update(child);
	}

	if (auto en = std::dynamic_pointer_cast<Entity>(e))
	{
		std::shared_ptr<Sprite> sp = std::dynamic_pointer_cast<Sprite>(en->texture);

		if (sp)
			if (sp->Current_Animation())
				sp->Current_Animation()->Next_Frame();

		en->Update();

		if (en->movement && sp)
		{
			if (Movement::__Resolve_Movement(en))
				sp->operator[]("move").Play();
			else if (sp->Current_Animation())
				sp->Current_Animation()->Terminate();
		}

		if (sp && !sp->Current_Animation()) sp->operator[]("idle").Play();
	}
}

void State::__Events(std::shared_ptr<Object> e)
{
	if (auto c = std::dynamic_pointer_cast<Container>(e))
	{
		for(auto child : c->children)
			__Events(child);
	}
	if(auto en = std::dynamic_pointer_cast<Entity>(e)) en->Events();
}

bool State::__isDeleted(std::shared_ptr<State> stt)
{
	for (unsigned i = 0; i < Built.size(); i++)
		if(stt == Built[i])
			for (unsigned j = 0; j < Deleted.size(); j++)
				if (Deleted[j] == i) return true;
	return false;
}

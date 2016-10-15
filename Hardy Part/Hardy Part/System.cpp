#include "System.h"
#include "State.h"
#include "Screen.h"
#include "Timer.h"
#include "Generic.h"
#include "Entity.h"
#include "Collider.h"
#include <iostream>

SDL_Event System::Events;
Timer System::FPS_Clock;
Timer System::In_Game_Timer;
unsigned System::FPS = 60;


void System::_System_Update()
{
	bool Quit_System = false;

	In_Game_Timer.Start();
	FPS_Clock.Start();

	if (!System::FPS || System::FPS > 1000) System::FPS = 60;

	while (!Quit_System)
	{
		if (FPS_Clock.Get() > 1000 / System::FPS)
		{
			FPS_Clock.Restart();
			if (State::Deleted.size()) __Delete();
			if (State::Built.size()) __Update();
			else { Quit_System = true; break; }

			while (SDL_PollEvent(&System::Events))
			{
				if (System::Events.type == SDL_QUIT) { State::Exit_Game(); break; }
				__Events();
			}
		}
		SDL_Delay(1);
	}

	Player::RemoveAll();
	Screen::Exit();
	TTF_Quit();
	SDL_Quit();
}

void System::__Update()
{
	Keyboard::Get.Update();
	Collider::Update();
	std::vector<State*> stt_to_update;
	for (unsigned i = 0; i < State::Built.size(); i++)
	{
		if (!State::Built[i]->Update_Underneath) stt_to_update.clear();
		stt_to_update.push_back(State::Built[i].get());
	}
	for (unsigned i = 0; i < stt_to_update.size(); i++)
	{
		stt_to_update[i]->Update();
		stt_to_update[i]->State::Update();
	}
	Player::__Update();
}
void System::__Events()
{
	unsigned size = State::Built.size();
	Device::Events();
	std::vector<State*> stt_to_events;
	for (unsigned i = 0; i < size; i++)
	{
		bool isDeleted = false;
		for (auto d : State::Deleted)
			if (d == i) { isDeleted = true; break; }
		if (isDeleted) continue;
		if (!State::Built[i]->Update_Underneath) stt_to_events.clear();
		stt_to_events.push_back(State::Built[i].get());

		//if (!Screen::Is_Windowed() && System::Events.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		//	for (auto ent : State::Built[i]->Get_Entities())
		//		if (dynamic_cast<Generic*>(ent->Display()))
		//			dynamic_cast<Generic*>(ent->Display())->Reload();
	}
	for (unsigned i = 0; i < stt_to_events.size(); i++)
	{
		stt_to_events[i]->Events();
		stt_to_events[i]->State::Events();
	}
	Device::Events_CleanUp();
}




void System::__Delete()
{
	for (unsigned del : State::Deleted)
		for (unsigned i = 0; i < State::Built.size(); i++)
			if (i == del)
			{
				//for (auto& ent : State::Built[i]->__Entities)
				//	if (ent.use_count() == 2)
				//		Entity::Destroy(ent.get());
				if (State::Built[i] == nullptr) continue;
				State::Built[i]->__Entities.clear();
				State::Built[i] = nullptr;
				break;
			}
	for (auto it = State::Built.begin(); it != State::Built.end();)
	{
		if (!(*it)) it = State::Built.erase(it);
		else ++it;
	}
	State::Deleted.clear();
}

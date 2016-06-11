#include "System.h"
#include "State.h"
#include "Screen.h"
#include "Timer.h"
#include "Tileset.h"
#include "Entity.h"
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
	Screen::Exit();
}

void System::__Update()
{
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
	Device::Events();
	std::vector<State*> stt_to_events;
	for (unsigned i = 0; i < State::Built.size(); i++)
	{
		if (!State::Built[i]->Update_Underneath) stt_to_events.clear();
		stt_to_events.push_back(State::Built[i].get());

		if (!Screen::Is_Windowed() && System::Events.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
			for (auto ent : State::Built[i]->Get_Entities())
				if (ent->As<Tileset>())
					Tileset::Reset(ent->As<Tileset>());
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
			if (i == del) { State::Built[i] = nullptr; break; }
	for (unsigned i = 0; i < State::Built.size(); i++)
		if (State::Built[i] == nullptr) State::Built.erase(State::Built.begin() + i--);
	State::Deleted.clear();
}

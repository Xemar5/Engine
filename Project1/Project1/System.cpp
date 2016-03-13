#include "System.h"
#include "State.h"
#include "Screen.h"
#include "Timer.h"
#include "Input_Handler.h"
#include "Movement_Handler.h"

SDL_Event System::Events;
Timer System::FPS_Clock;
unsigned System::FPS = 60;


void System::_System_Update()
{
	bool Quit_System = false;

	Movement_Handler::Set("mama", "int", 'l', 333, 3.0, 0.0, 4.2);

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
			Input_Handler::__Input_Update();

			while (SDL_PollEvent(&System::Events))
			{
				if (System::Events.type == SDL_QUIT) { State::Exit_Game(); break; }
				Input_Handler::__Input_Events();
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
		stt_to_update[i]->Update();
}
void System::__Events()
{
	std::vector<State*> stt_to_events;
	for (unsigned i = 0; i < State::Built.size(); i++)
	{
		if (!State::Built[i]->Update_Underneath) stt_to_events.clear();
		stt_to_events.push_back(State::Built[i].get());
	}
	for (unsigned i = 0; i < stt_to_events.size(); i++)
		stt_to_events[i]->Events();
}
void System::__Delete()
{
	for (unsigned del : State::Deleted)
		for (unsigned i = 0; i < State::Built.size(); i++)
			if (i == del) State::Built[i] = nullptr;
	for (unsigned i = 0; i < State::Built.size(); i++)
		if (State::Built[i] == nullptr) State::Built.erase(State::Built.begin() + i--);
	State::Deleted.clear();
}

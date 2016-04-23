#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <memory>
#include <stdio.h>
//#include "State.h"

class Timer;



class System final
{
public:
	//*** Initialises the system with given State
	template <typename T>
	static void Start();

	//*** SDL Event handler
	static SDL_Event Events;
	//*** The timer that resets everytime the frame should be updated
	//*** Adjust the FPS to make it reset faster/slower
	static Timer FPS_Clock;
	//*** The timer that starts at the beginning of the program
	static Timer In_Game_Timer;
	//*** The approximate number of frames per second
	static unsigned FPS;

	//*** The main music holder
	static Mix_Music* Soundtrack;
protected:

	//*** Main System loop, where all the states are updated
	static void _System_Update();
private:
	static void __Delete();
	static void __Update();
	static void __Events();
	
};

#include "Screen.h"

template <typename T>
void System::Start()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	System::Soundtrack = Mix_LoadMUS("imgs/Baker Cat.mp3");
	Mix_PlayMusic(System::Soundtrack, -1);
	Screen::Start();
	State::New<T>();
	//Screen::Change_Window_State();
	_System_Update();
}

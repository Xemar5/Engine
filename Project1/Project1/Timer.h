#pragma once
#include <SDL.h>

class Timer
{
public:
	//*** Starts the timer
	Uint32 Start();
	//*** Stops the timer and sets it's all parameters to 0
	Uint32 Stop();
	//*** Stops the timer and then starts it back again with all parameters equal to 0
	Uint32 Restart();
	//*** Pauses the timer, it runs in the background
	//*** Unpause it with Unpause function
	Uint32 Pause();
	//*** Unpauses the paused timer
	Uint32 Unpause();
	//*** Returns the current time on the timer
	Uint32 Get();

	//*** Returns true id the timer is started
	bool Is_Started();
	//*** Returns true if the timer is paused
	bool Is_Paused();
private:
	//*** Sets the starting time of the timer, depends only on when the timer started
	Uint32 __Time_Before_Start = 0;
	//*** Counts the time of the timer being paused
	Uint32 __Time_Paused = 0;
	//*** Counts the time of the timer since start
	Uint32 __Time = 0;

	//*** If true, the timer is started
	bool __Started = false;
	//*** If true, the timer is started but paused
	bool __Paused = false;
};
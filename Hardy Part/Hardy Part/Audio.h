#pragma once
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include <memory>


class Track
{
public:
	//*** The actual Music sample
	Mix_Music* Music = nullptr;
	//*** Returns the path to this track
	std::string Get_Path();
private:
	//*** The path this track was loaded from
	//*** Prevents loading one track multiple times
	std::string __Path = "";

	friend class Audio;
};


class Audio
{
public:
	//*** Initializes the Sound class
	static bool Init();

	//*** The main music holder
	static Track* Current_Track;
	//*** Stores all the loaded music
	static std::vector<std::shared_ptr<Track>> Tracklist;
	//*** Loads the track from given path if it exists
	//*** If succesful, adds the track to the tracklist
	static Track* Load_Music(std::string path);

	//*** Plays the given music track if it exists
	//*** - loops - the number of loops this track is going to play 
	//***		    set to -1 to play infinite
	static bool Play_Music(Track* track, int loops = -1);

private:
	//*** If true, the Sound class has already been initialized
	static bool __Initialized;
};
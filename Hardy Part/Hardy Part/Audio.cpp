#include "Audio.h"
#include "Output_Handler.h"

Track* Audio::Current_Track = nullptr;
std::vector<std::shared_ptr<Track>> Audio::Tracklist;
bool Audio::__Initialized = false;



std::string Track::Get_Path()
{
	return __Path;
}





bool Audio::Init()
{
	if (Audio::__Initialized)
	{
		Output_Handler::Output << "MSG Sound::Init : Sound already initialized\n";
		return false;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Audio::__Initialized = true;
	return true;
}

Track * Audio::Load_Music(std::string path)
{
	for (auto tr : Audio::Tracklist)
		if (tr->__Path == path) return tr.get();
	Mix_Music* ms = Mix_LoadMUS(path.c_str());
	if (!ms)
	{
		Output_Handler::Error << "ERR Sound::Load_Music : Given path (\"" << path << "\") stores no Music\n";
		return nullptr;
	}
	Tracklist.push_back(std::make_shared<Track>());
	Tracklist.back()->Music = ms;
	Tracklist.back()->__Path = path;
	return Tracklist.back().get();
}

bool Audio::Play_Music(Track * track, int loops)
{
	if (!Audio::__Initialized)
	{
		Output_Handler::Error << "ERR Sound::Play_Music : Sound not initialized; use Sound::Init first\n";
		return false;
	}
	if (!track)
	{
		Output_Handler::Error << "ERR Sound::Play_Music : No Track supplied\n";
		return false;
	}
	Mix_PlayMusic(track->Music, loops);
	return true;
}

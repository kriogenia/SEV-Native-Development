#pragma once

#include <iostream>
#include <string> 
#include <SDL.h>;
#include <SDL_mixer.h> 

using namespace std;

class Audio
{
public:
	Audio(string filename, bool loop);
	~Audio();

	void play();
	bool loop;

	Mix_Music* mix;					// Lib mixer
	SDL_AudioSpec wavSpec;			// Lib SDL Standard
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;
};

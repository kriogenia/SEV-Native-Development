#pragma once

#include <iostream>
#include <string>
using namespace std;

#include <SDL.h>
#include <SDL_mixer.h>

class Audio {
public:
	Audio(string filename, bool loop);
	~Audio();

	void play();

	bool loop;

	Mix_Music* mix;			// library mixer
	SDL_AudioSpec wavSpec;	// lib SDL standard
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceID;
};


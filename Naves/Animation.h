#pragma once

#include "Game.h"

class Animation
{
public:
	Animation(string filename, float actorWidth, float actorHeight, float fileWidth, 
		float fileHeight, int updateFrecuence, int totalFrames, Game* game);

	bool update();
	void draw(float x, float y);

	int actorWidth;
	int actorHeight;
	int fileWidth;
	int fileHeight;
	int currentFrame;
	int totalFrames;
	Game* game;

	// Auxiliary vars
	SDL_Texture* texture;		// image
	SDL_Rect source;			// taken part of the file
	float frameWidth;
	float frameHeight;			// frame dimensions
	int updateFrecuence = 0;
	int updateTime = 0;

};


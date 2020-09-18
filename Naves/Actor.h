#pragma once

#include "Game.h"

class Actor
{
	Actor(string filename, float x, float y, int width, int height, int fileWidth, int fileHeight);
	virtual void draw();

	SDL_Texture* texture;
	float x;
	float y;
	float vx;
	float vy;
	int width;
	int height;
	int fileWidth;
	int fileHeight;

	Game* game;
};


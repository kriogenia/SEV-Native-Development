#pragma once

#include "Game.h"

class Actor {
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();

	virtual void draw(float scrollX = 0);
	virtual bool isInRender(float scrollX = 0);
	bool isOverlap(Actor* actor);

	SDL_Texture* texture;

	bool collisionDown;
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
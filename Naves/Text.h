#pragma once

#include "Game.h"

class Text
{
public:
	Text(string content, float x, float y, Game* game);
	void draw();

	string content;
	int x;
	int y;
	int height;
	int width;
	Game* game;
};


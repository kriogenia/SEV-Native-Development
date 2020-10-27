#pragma once

#include "Actor.h"

class MovingTile : public Actor
{
public:
	MovingTile(string filename, float x, float y, Game* game);

	void update();

	int vxDirection = -1;
	int vyDirection = -1;
};

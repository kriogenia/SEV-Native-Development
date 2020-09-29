#pragma once

#include "Actor.h"
#include "Player.h"

class PickUp : public Actor
{
public:
	PickUp(string filename, float x, float y, int width, int height, Game* game);

	virtual void doEffect(Player* player, int* points);
};


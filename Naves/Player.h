#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);

	void update();
	void moveX(float direction);
	void moveY(float direction);

};


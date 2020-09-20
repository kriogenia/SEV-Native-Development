#pragma once

#include "Actor.h"
#include "Projectile.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);

	void update();
	void moveX(float direction);
	void moveY(float direction);
	Projectile* shoot();

	int shootCadence = 30;
	int shootTime = 0;

};

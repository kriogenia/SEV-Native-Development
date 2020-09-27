#pragma once

#include "Actor.h"

class Projectile : public Actor
{
public:
	Projectile(float x, float y, int power, Game* game);
	void update();
	bool isOutOfRender() override;
};


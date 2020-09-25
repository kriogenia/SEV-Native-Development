#pragma once

#include "Actor.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void update();
	void draw() override;
	bool isOutOfRender() override;

	Animation* aMoving;
	Animation* animation;
};


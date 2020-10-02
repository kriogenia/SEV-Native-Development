#pragma once

#include "Actor.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);

	void update();
	void draw(float scrollX = 0) override;
	bool isOutOfRender() override;
	void impacted();

	int state;

	Animation* aMoving;
	Animation* aDying;
	Animation* animation;
};


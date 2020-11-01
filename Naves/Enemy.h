#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Projectile.h"

class Enemy :
    public Actor
{
public:
	Enemy(string filename, float x, float y, int width, int height, Game* game);

	virtual void update();
	void draw(float scrollX = 0) override;
	void impacted();
	virtual Projectile* doAction();

	int state;
	float vxIntelligence;

	Animation* aMoving;
	Animation* aDying;
	Animation* animation;
};


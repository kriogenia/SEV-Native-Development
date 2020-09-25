#pragma once

#include "Actor.h"
#include "Animation.h"
#include "EnemyProjectile.h"

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);

	void update();
	void draw() override;
	bool isOutOfRender() override;
	EnemyProjectile* autoshoot();

	Animation* aMoving;
	Animation* animation;

	int shotCadence = 50;
};


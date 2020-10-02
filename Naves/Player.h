#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Animation.h"
#include "Audio.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);

	void update();
	void draw(float scrollX = 0) override;
	void moveX(float direction);
	void moveY(float direction);

	Projectile* shoot();
	Audio* audioShoot;

	int shootCadence = 30;
	int shootTime = 0;
	int state;
	int orientation;

	Animation* animation;

	Animation* aIdleRight;
	Animation* aIdleLeft;
	
	Animation* aRunningRight;
	Animation* aRunningLeft;

	Animation* aShootingRight;
	Animation* aShootingLeft;

};

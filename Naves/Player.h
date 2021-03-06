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
	void jump();
	void loseLife();

	Projectile* shoot();
	Audio* audioShoot;

	int invulnerableTime = 0;
	int lifes = 3;
	bool onAir;
	int orientation;
	int shootCadence = 30;
	int shootTime = 0;
	int state;

	Animation* animation;

	Animation* aIdleRight;
	Animation* aIdleLeft;

	Animation* aJumpingRight;
	Animation* aJumpingLeft;
	
	Animation* aRunningRight;
	Animation* aRunningLeft;

	Animation* aShootingRight;
	Animation* aShootingLeft;

};

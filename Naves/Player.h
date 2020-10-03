#pragma once

#include "Actor.h"
#include "Audio.h"
#include "Projectile.h"
#include "Text.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	~Player();

	void update();
	void moveX(float direction);
	void moveY(float direction);
	void receiveDamage(Text* hpText);

	Projectile* shoot();

	Audio* audioCoin;
	Audio* audioDamage;
	Audio* audioDetonateBomb;
	Audio* audioLife;
	Audio* audioPowerUp;
	Audio* audioShoot;

	int hp = 3;
	int power = 1;
	int shootCadence = 30;
	int shootTime = 0;

};


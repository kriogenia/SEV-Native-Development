#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "PickUp.h"

#include <list>

class GameLayer: public Layer
{
public:

	GameLayer(Game* game);

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);

	Player* player;
	Background* background;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<PickUp*> pickups;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;
	int newEnemyTime = 0;
	int killCount = 0;
	int newPickUpTime = 0;

};


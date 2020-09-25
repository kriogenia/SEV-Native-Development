#pragma once

#include "Audio.h"
#include "Background.h"
#include "Bomb.h"
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "Layer.h"
#include "Player.h"
#include "Projectile.h"
#include "Text.h"

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
	Actor* backgroundPoints;
	Audio* audioBackground;
	Text* textPoints;

	list<Bomb*> bombs;
	list<Enemy*> enemies;
	list<EnemyProjectile*> enemyProjectiles;
	list<Projectile*> projectiles;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;
	int newEnemyTime = 0;
	int newBombTime = 500;
	int points = 0;

};


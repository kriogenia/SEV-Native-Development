#pragma once

#include "Audio.h"
#include "Background.h"
#include "Enemy.h"
#include "Layer.h"
#include "Pad.h"
#include "Player.h"
#include "Projectile.h"
#include "Space.h"
#include "Text.h"
#include "Tile.h"

#include <fstream>
#include <list>
#include <sstream>

class GameLayer: public Layer
{
public:

	GameLayer(Game* game);

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event);

	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();

	Background* background;
	Player* player;
	Space* space;
	Tile* cup;

	Actor* buttonJump;
	Actor* buttonShoot;
	Pad* pad;

	Actor* backgroundPoints;
	Audio* audioBackground;
	Text* textPoints;

	list<Enemy*> enemies;
	list<Tile*> tiles;
	list<Projectile*> projectiles;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;
	int newEnemyTime = 0;
	int points = 0;

	int mapWidth;
	float scrollX;

};


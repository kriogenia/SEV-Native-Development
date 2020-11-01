#pragma once

#include "Enemy.h"

class ShipEnemy : public Enemy
{
public:
	ShipEnemy(float x, float y, Game* game);

	void update() override;
};


#pragma once

#include "PickUp.h"

class PowerUp : public PickUp
{
public:
	PowerUp(float x, float y, Game* game);

	void doEffect(Player* player, int* points) override;
};


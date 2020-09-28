#pragma once

#include "PickUp.h"

class Coin : public PickUp
{
public:
	Coin(float x, float y, Game* game);

	void doEffect(Player* player, int* points) override;
};


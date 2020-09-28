#pragma once

#include "PickUp.h"

class Life : public PickUp
{
public:
	Life(float x, float y, Game* game);

	void doEffect(Player* player, int* points) override;
};


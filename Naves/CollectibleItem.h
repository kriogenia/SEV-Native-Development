#pragma once

#include "Actor.h"
#include "Animation.h"

class CollectibleItem : public Actor
{
public:
	CollectibleItem(float x, float y, Game* game);
	void draw(float scrollX = 0) override;

	Animation* animation;
};


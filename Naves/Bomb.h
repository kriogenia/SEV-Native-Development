#pragma once

#include "Actor.h"
#include "Audio.h"

class Bomb : public Actor {
public:
	Bomb(float x, float y, Game* game);

	Audio* explosionAudio;

};


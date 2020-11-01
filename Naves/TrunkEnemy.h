#pragma once

#include "Enemy.h"

class TrunkEnemy :
    public Enemy
{
public:
    TrunkEnemy(float x, float y, Game* game);

    void update() override;

    Animation* aShooting;

};


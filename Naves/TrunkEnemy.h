#pragma once

#include "Enemy.h"

class TrunkEnemy :
    public Enemy
{
public:
    TrunkEnemy(float x, float y, Game* game);

    void update() override;
    Projectile* doAction() override;

    Animation* aShooting;

    int shootTime;
    int shootCadence;

};


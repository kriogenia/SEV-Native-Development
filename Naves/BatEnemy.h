#pragma once
#include "Enemy.h"
class BatEnemy :
    public Enemy
{
public:
    BatEnemy(float x, float y, Game* game);

    void update() override;

    int angle = 0;
};


#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game){
	vx = 1;
}

void Enemy::update() {
	vx = -1;
	x = x + vx;
}

bool Enemy::isOut() {
	return x + width/2 <= 0;
}
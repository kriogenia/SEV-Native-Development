#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game){
	vx = 1;

	aMoving = new Animation("res/enemigo_movimiento.png", width, height, 108, 40, 6, 3, game);
	animation = aMoving;
}

void Enemy::update() {
	animation->update();
	vx = -1;
	x = x + vx;
	shotCadence--;
}

void Enemy::draw() {
	animation->draw(x, y);
}

bool Enemy::isOutOfRender() {
	return x + width/2 <= 0;
}

EnemyProjectile* Enemy::autoshoot() {
	if (shotCadence <= 0) {
		shotCadence = 50;
		return new EnemyProjectile(x, y, game);
	}
	else {
		return NULL;
	}
}
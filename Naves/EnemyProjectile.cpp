#include "EnemyProjectile.h"

EnemyProjectile::EnemyProjectile(float x, float y, Game* game)
	: Actor("res/disparo_enemigo.png", x, y, 20, 20, game) {
	vx = ((rand() % (9 - 3)) + 1 + 3) * -1;
}

void EnemyProjectile::update() {
	x = x + vx;
}

bool EnemyProjectile::isOutOfRender() {
	return x <= 0;
}
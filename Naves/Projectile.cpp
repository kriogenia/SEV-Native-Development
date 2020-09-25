#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game)
	: Actor("res/disparo_jugador.png", x, y, 18, 6, game) {
	vx = 9;
}

void Projectile::update() {
	x = x + vx;
}

bool Projectile::isOutOfRender() {
	return x >= WIDTH;
}
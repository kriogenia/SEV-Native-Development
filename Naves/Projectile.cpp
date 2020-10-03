#include "Projectile.h"

Projectile::Projectile(float x, float y, int power, Game* game)
	: Actor("res/disparo_jugador.png", x, y, 18 * power, 6 * power, game) {
	vx = 9;
}

void Projectile::update() {
	x = x + vx;
}
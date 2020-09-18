#include "Player.h"
#include "Projectile.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game)
{

}

void Player::update() {
	if (shootTime > 0) {
		shootTime--;
	}
	x = x + vx;
	y = y + vy;
}

void Player::moveX(float direction) {
	vx = 3 * direction;
}

void Player::moveY(float direction) {
	vy = 3 * direction;
}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		shootTime = shootCadence;
		return new Projectile(x, y, game);
	}
	else {
		return NULL;
	}

}
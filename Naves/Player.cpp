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
	if (x - width/2 < 0) {
		x = width/2;
	}
	else if (x + width/2 > WIDTH) {
		x = WIDTH - width / 2;
	}
	y = y + vy;
	if (y - height/2 < 0) {
		y = height/2;
	}
	else if (y + height/2 > HEIGHT) {
		y = HEIGHT - height / 2;
	}
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
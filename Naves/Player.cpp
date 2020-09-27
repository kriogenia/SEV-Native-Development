#include "Player.h"
#include "Projectile.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game) {

	audioShoot = new Audio("res/efecto_disparo.wav", false);
	audioDamage = new Audio("res/efecto_hit.wav", false);
	audioPowerUp = new Audio("res/efecto_powerup.wav", false);

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
		audioShoot->play();
		shootTime = shootCadence/power;
		return new Projectile(x, y, power, game);
	}
	else {
		return NULL;
	}

}
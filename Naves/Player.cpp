#include "Player.h"
#include "Projectile.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game) {

	audioCoin = new Audio("res/efecto_moneda.wav", false);
	audioDamage = new Audio("res/efecto_hit.wav", false);
	audioDetonateBomb = new Audio("res/efecto_explosion.wav", false);
	audioLife = new Audio("res/efecto_vida.wav", false);
	audioPowerUp = new Audio("res/efecto_powerup.wav", false);
	audioShoot = new Audio("res/efecto_disparo.wav", false);

}

Player::~Player() {
	delete audioCoin;
	delete audioDamage;
	delete audioDetonateBomb;
	delete audioLife;
	delete audioPowerUp;
	delete audioShoot;
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

void Player::receiveDamage(Text* hpText) {
	hp--;
	audioDamage->play();
	hpText->content = to_string(hp);
	cout << "Contact! - HP: " << hp << endl;
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
#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game)
{

}

void Player::update() {
	x = x + vx;
	y = y + vy;
}

void Player::moveX(float direction) {
	vx = 3 * direction;
}

void Player::moveY(float direction) {
	vy = 3 * direction;
}
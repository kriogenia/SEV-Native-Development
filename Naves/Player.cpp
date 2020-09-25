#include "Player.h"
#include "Projectile.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 50, 57, game) {

	state = game->stateMoving;
	orientation = game->orientationRight;

	aIdleRight = new Animation("res/jugador_idle_derecha.png", width, height,
		320, 40, 6, 8, true, game);
	aIdleLeft = new Animation("res/jugador_idle_izquierda.png", width, height,
		320, 40, 6, 8, true, game);

	aRunningRight = new Animation("res/jugador_corriendo_derecha.png", width, height,
		320, 40, 6, 8, true, game);
	aRunningLeft = new Animation("res/jugador_corriendo_izquierda.png", width, height,
		320, 40, 6, 8, true, game);

	aShootingRight = new Animation("res/jugador_disparando_derecha.png", width, height,
		160, 40, 6, 4, false, game);
	aShootingLeft = new Animation("res/jugador_disparando_izquierda.png", width, height,
		160, 40, 6, 4, false, game);

	animation = aIdleRight;

}

void Player::update() {
	bool endAnimation = animation->update();

	if (endAnimation) {
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}

	if (vx > 0) {
		orientation = game->orientationRight;
	}
	else if (vx < 0) {
		orientation = game->orientationLeft;
	}

	if (state == game->stateShooting) {
		if (orientation == game->orientationRight) {
			animation = aShootingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aShootingLeft;
		}
	}

	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}

		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
	}


	if (shootTime > 0) {
		shootTime--;
	}
	x = x + vx;
	y = y + vy;
}

void Player::draw() {
	animation->draw(x, y);
}

void Player::moveX(float direction) {
	vx = 3 * direction;
}

void Player::moveY(float direction) {
	vy = 3 * direction;
}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		state = game->stateShooting;
		shootTime = shootCadence;

		aShootingLeft->currentFrame = 0;
		aShootingRight->currentFrame = 0;

		auto projectile = new Projectile(x, y, game);
		if (orientation == game->orientationLeft) {
			projectile->vx = projectile->vx * -1;
		}
		return projectile;
	}
	else {
		return NULL;
	}

}
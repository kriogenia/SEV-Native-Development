#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game){
	state = game->stateMoving;
	vx = 1;

	aMoving = new Animation("res/enemigo_movimiento.png", width, height, 108, 40, 6, 3, true, game);
	aDying = new Animation("res/enemigo_morir.png", width, height, 280, 40, 6, 8, false, game);
	animation = aMoving;

}

void Enemy::update() {
	bool endAnimation = animation->update();

	if (endAnimation) {
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	} else {
		vx = -1;
		x = x + vx;
	}

}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

void Enemy::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}
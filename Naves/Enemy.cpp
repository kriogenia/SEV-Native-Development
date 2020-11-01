#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, int width, int height, Game* game) :
	Actor(filename, x, y, width, height, game) {

	state = game->stateMoving;
	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;

}

void Enemy::update() {}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

void Enemy::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}

void Enemy::doAction() {}
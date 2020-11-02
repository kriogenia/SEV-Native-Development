#include "BatEnemy.h"

BatEnemy::BatEnemy(float x, float y, Game* game) :
	Enemy("res/enemy3.png", x, y, 46, 30, game) {

	state = game->stateMoving;
	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;
	vy = (sin(angle * 3.1416 / 180) * 10) - 1;

	aMoving = new Animation("res/enemy3_moving.png", width, height, 322, 30, 1, 7, true, game);
	aDying = new Animation("res/enemy3_dead.png", width, height, 230, 30, 6, 5, false, game);
	animation = aMoving;
}

void BatEnemy::update() {
	angle += 30;
	if (state != game->stateDying) {
		vy = (sin(angle * 3.1416 / 180) * 10) - 1;
	}

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
	}
	if (state != game->stateDying) {
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}
	}
	else {
		vx = 0;
	}
}
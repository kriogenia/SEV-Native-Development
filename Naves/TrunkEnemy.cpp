#include "TrunkEnemy.h"

TrunkEnemy::TrunkEnemy(float x, float y, Game* game) :
	Enemy("/res/enemy2.png", x, y, 64, 32, game) {
	state = game->stateMoving;
	vx = 2;
	vxIntelligence = -2;
	vx = vxIntelligence;

	aMoving = new Animation("res/enemy2_anim.png", width, height, 896, 32, 6, 14, true, game);
	aDying = new Animation("res/enemy2_dead.png", width, height, 320, 32, 6, 5, false, game);
	aShooting = new Animation("res/enemy2_attack.png", width, height, 704, 32, 0, 11, false, game);

	animation = aMoving;

	shootCadence = 60;
	shootTime = shootCadence;
}

void TrunkEnemy::update() {
	bool endAnimation = animation->update();

	if (endAnimation) {
		if (state == game->stateDying) {
			state = game->stateDead;
		}
		else if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	else if (state == game->stateShooting) {
		animation = aShooting;
	}
	else if (state == game->stateDying) {
		animation = aDying;
	}
	if (state != game->stateDying) {
		// moving and stopped
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}
	}
	else {
		vx = 0;
	}

}

Projectile* TrunkEnemy::doAction() {
	shootTime--;
	if (shootTime == 0 && state != game->stateDying) {
		state = game->stateShooting;
		aShooting->currentFrame = 0;
		shootTime = shootCadence;
	}
	if (state == game->stateShooting && aShooting->currentFrame == 5) {
		Projectile* projectile = new Projectile("res/enemy2_bullet.png", x, y, 16, 16, game);
		projectile->vx = -5;
		projectile->vy = 0;
		return projectile;
	}
	return nullptr;
}
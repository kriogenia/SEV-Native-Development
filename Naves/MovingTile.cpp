#include "MovingTile.h"

MovingTile::MovingTile(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 40, 32, game) {
	vx = vxDirection;
	vy = vyDirection;
}

void MovingTile::update() {
	if (vx == 0) {
		vxDirection = vxDirection * -1;
		vx = vxDirection;
	}
	vy = vyDirection;
}
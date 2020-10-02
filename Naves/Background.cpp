#include "Background.h"

Background::Background(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, WIDTH, HEIGHT, game){

};

Background::Background(string filename, float x, float y, float vx, Game* game)
	: Actor(filename, x, y, WIDTH, HEIGHT, game) {
	this->vx = vx;

	if (vx != 0) {
		bgAux = new Background(filename, x+WIDTH, y, game);
	}

};

void Background::update() {
	if (vx != 0) {
		x = x + vx;

		if (x + width / 2 < 0) {
			x = WIDTH + width / 2;
		}

		if (x - width / 2 > WIDTH) {
			x = 0 - width / 2;
		}
	}
}

void Background::draw(float scrollX) {
	Actor::draw();

	if (bgAux != nullptr) {
		if (x - width / 2 > 0) {
			bgAux->x = x - width;
		}
		if (x + width / 2 < WIDTH) {
			bgAux->x = x + width;
		}

		bgAux->draw();
	}
}
#include "PickUp.h";

PickUp::PickUp(string filename, float x, float y, int width, int height, Game* game)
	: Actor(filename, x, y, width, height, game) {
}

void PickUp::doEffect(Player* player, int* points) {
	points++;
}
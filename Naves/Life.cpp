#include "Life.h"

Life::Life(float x, float y, Game* game)
	: PickUp("res/corazon.png", x, y, 44, 36, game) {
	audioPickUp = new Audio("res/efecto_moneda.wav", false);
}

void Life::doEffect(Player* player, int* points) {
	if (player->hp < 3) {
		player->hp++;
	}
	PickUp::doEffect(player, points);
}
#include "Life.h"

Life::Life(float x, float y, Game* game)
	: PickUp("res/corazon.png", x, y, 44, 36, game) {
}

void Life::doEffect(Player* player, int* points) {
	if (player->hp < 3) {
		player->hp++;
	}
	player->audioLife->play();
}
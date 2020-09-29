#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, Game* game)
	: PickUp("res/icono_recolectable.png", x, y, 40, 40, game) {
}

void PowerUp::doEffect(Player* player, int* points) {
	if (player->power == 1) {
		player->power = 2;
		player->audioPowerUp->play();
	}
	else {
		if (player->hp < 3) {
			player->hp++;
			player->audioLife->play();
		}
		else {
			++* points;
			player->audioCoin->play();
		}
	}
}
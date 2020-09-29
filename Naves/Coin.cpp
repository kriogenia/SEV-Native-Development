#include "Coin.h"

Coin::Coin(float x, float y, Game* game)
	: PickUp("res/moneda.png", x, y, 40, 40, game) {
}

void Coin::doEffect(Player* player, int* points) {
	++* points;
	player->audioCoin->play();
}
#include "Coin.h"

Coin::Coin(float x, float y, Game* game)
	: PickUp("res/moneda.png", x, y, 40, 40, game) {
	audioPickUp = new Audio("res/efecto_moneda.wav", false);
}

void Coin::doEffect(Player* player, int* points) {
	++* points;
	PickUp::doEffect(player, points);
}
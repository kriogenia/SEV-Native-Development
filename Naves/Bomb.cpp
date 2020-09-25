#include "Bomb.h"

Bomb::Bomb(float x, float y, Game* game)
	:Actor("res/asteroide.png", x, y, 50, 51, game) {

	delete explosionAudio;
	explosionAudio = new Audio("res/efecto_explosion.wav", false);
}
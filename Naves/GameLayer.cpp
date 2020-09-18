#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	init();
}

void GameLayer::init() {
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	player = new Player(50, 50, game);

}

void GameLayer::processControls() {

}

void GameLayer::update() {
	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();
	player->draw();
	SDL_RenderPresent(game->renderer);
}
#include "Game.h"
#include "GameLayer.h"

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error SDL_Init" << SDL_GetError() << endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
		cout << "Error Window y Renderer" << SDL_GetError() << endl;
	}
	SDL_SetWindowTitle(window, "Juego de Naves");
	// Quality image rendering 
	// https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gameLayer = new GameLayer(this);

	loopActive = true;
	loop();
}

void Game::loop() {
	int initTick;
	int endTick;
	int differenceTick;

	while (loopActive) {
		initTick = SDL_GetTicks();

		// Controls
		gameLayer->processControls();
		// Update elements
		gameLayer->update();
		// Draw
		gameLayer->draw();

		endTick = SDL_GetTicks();
		differenceTick = endTick - initTick;

		if (differenceTick < (1000 / 30)) {
			SDL_Delay((1000 / 30) - differenceTick);
		}
	}

}

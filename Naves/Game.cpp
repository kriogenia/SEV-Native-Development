#include "Game.h"
#include "GameLayer.h"
#include "MenuLayer.h"

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error SDL_Init" << SDL_GetError() << endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
		cout << "Error Window and Renderer" << SDL_GetError() << endl;
	}
	SDL_SetWindowTitle(window, "Juego de Naves");
	// Quality image rendering 
	// https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gameLayer = new GameLayer(this);
	menuLayer = new MenuLayer(this);
	layer = menuLayer;

	TTF_Init();
	font = TTF_OpenFont("res/sans.ttf", 24);

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
		layer->processControls();
		// Update elements
		layer->update();
		// Draw
		layer->draw();

		endTick = SDL_GetTicks();
		differenceTick = endTick - initTick;

		if (differenceTick < (1000 / 30)) {
			SDL_Delay((1000 / 30) - differenceTick);
		}
	}
}

void Game::scale() {
	scaledToMax = !scaledToMax;

	if (scaledToMax) {
		SDL_DisplayMode PCdisplay;
		SDL_GetCurrentDisplayMode(0, &PCdisplay);
		float scaleX = (float)PCdisplay.w / (float)WIDTH;
		float scaleY = (float)PCdisplay.h / (float)HEIGHT;
		// We get the lower of the two scales
		scaleLower = scaleX;
		if (scaleY < scaleX) {
			scaleLower = scaleY;
		}
		// Change window size and render scale
		SDL_SetWindowSize(window, WIDTH * scaleLower, HEIGHT * scaleLower);
		SDL_RenderSetScale(renderer, scaleLower, scaleLower);
	}
	else { 
		scaleLower = 1;
		// Change window size and render scale
		SDL_SetWindowSize(window, WIDTH, HEIGHT);
		SDL_RenderSetScale(renderer, 1, 1);
	}

}

SDL_Texture* Game::getTexture(string filename) {
	if (mapTextures.find(filename) != mapTextures.end()) {
		cout << "Cached resource returned -> " << filename << endl;
	}
	else {
		cout << "New resource to cache -> " << filename << endl;
		SDL_Surface* surface = IMG_Load(filename.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		mapTextures[filename] = texture;
	}

	return mapTextures[filename];
}
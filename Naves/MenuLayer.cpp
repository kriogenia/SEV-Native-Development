#include "MenuLayer.h"

MenuLayer::MenuLayer(Game* game)
	: Layer(game) {
	init();
}

void MenuLayer::init() {
	background = new Background("res/menu_fondo.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	button = new Actor("res/boton_jugar.png", WIDTH * 0.5, HEIGHT * 0.7, 232, 72, game);
}

void MenuLayer::draw() {
	background->draw();
	button->draw();

	SDL_RenderPresent(game->renderer);
}

void MenuLayer::processControls() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			game->loopActive = false;
		case SDL_MOUSEBUTTONDOWN:
			game->input = GameInputType::MOUSE;
			break;
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERAXISMOTION:
			game->input = GameInputType::GAMEPAD;
			break;
		case SDL_KEYDOWN:
			game->input = GameInputType::KEYBOARD;
			break;
		}

		if (game->input == GameInputType::KEYBOARD)
			keysToControls(event);
		if (game->input == GameInputType::MOUSE)
			mouseToControls(event);
	}

	if (controlContinue) {
		game->layer = game->gameLayer;
		controlContinue = false;

	}
}

void MenuLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		switch (code) {
		case SDLK_1:
			game->scale();
			break;
		case SDLK_SPACE:
			controlContinue = true;
			break;
		}
	}
}

void MenuLayer::mouseToControls(SDL_Event event) {
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (button->containsPoint(motionX, motionY)) {
			controlContinue = true;
		}
	}
}
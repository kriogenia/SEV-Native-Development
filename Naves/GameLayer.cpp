#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	init();
}

void GameLayer::init() {

	delete background;
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, game);

	delete player;
	player = new Player(50, 50, game);

	enemies.clear();
	enemies.push_back(new Enemy(300, 50, game));
	enemies.push_back(new Enemy(300, 200, game));

	projectiles.clear();

}

void GameLayer::processControls() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}

	// Shooting
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
	}

	// Movement - Axis X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Movement - Axis Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}

}

void GameLayer::update() {
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	// Collisions
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			init();
			return;
		}
	}

	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();
	player->draw();

	for (auto const& enemy : enemies) {
		enemy->draw();
	}
	for (auto const& projectile : projectiles) {
		projectile->draw();
	}

	SDL_RenderPresent(game->renderer);
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Movement
		switch (code) {
		case SDLK_d:
			controlMoveX = 1;
			break;
		case SDLK_a:
			controlMoveX = -1;
			break;
		case SDLK_w:
			controlMoveY = -1;
			break;
		case SDLK_s:
			controlMoveY = 1;
			break;
		// Shoot
		case SDLK_SPACE:
			controlShoot = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Movement
		switch (code) {
		case SDLK_d:
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a:
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w:
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s:
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		// Shoot
		case SDLK_SPACE:
			controlShoot = false;
			break;
		}
	}

}

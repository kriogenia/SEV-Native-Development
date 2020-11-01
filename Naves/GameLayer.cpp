#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	init();
}

void GameLayer::init() {

	space = new Space(1);

	buttonJump = new Actor("res/boton_salto.png", WIDTH * 0.9, HEIGHT * 0.55, 100, 100, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);

	scrollX = 0;
	enemies.clear();
	items.clear();
	movingTiles.clear();
	tiles.clear();
	projectiles.clear(); 
	enemyProjectiles.clear();
	loadMap("res/" + to_string(game->currentLevel) + ".txt");

	points = 0;
	collected = 0;

	delete background;
	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);

	delete backgroundPoints;
	backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);
	delete backgroundItems;
	backgroundItems = new Actor("res/icono_recolectable.png", WIDTH * 0.85, HEIGHT * 0.15, 40, 40, game);

	delete audioBackground;
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();
	delete audioItem;
	audioItem = new Audio("res/efecto_moneda.wav", false);

	delete textPoints;
	textPoints = new Text("0", WIDTH * 0.92, HEIGHT * 0.05, game);
	textPoints->content = to_string(points);
	delete textItems;
	textItems = new Text("0", WIDTH * 0.92, HEIGHT * 0.15, game);
	textItems->content = to_string(collected);

}

void GameLayer::processControls() {
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

	// Shooting
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
			space->addDynamicActor(newProjectile);
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
	if (controlMoveY < 0) {
		player->jump();
	}

}

void GameLayer::update() {
	// Level won
	if (cup->isOverlap(player)) {
		game->currentLevel++;
		if (game->currentLevel > game->finalLevel) {
			game->currentLevel = 0;
		}
		init();
	}

	if (player->y > HEIGHT + player->height) {
		init();
	}

	space->update();
	background->update();

	// Actors update
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
		Projectile* projectile = enemy->doAction();
		if (projectile != nullptr) {
			enemyProjectiles.push_back(projectile);
			space->addDynamicActor(projectile);
		}
	}
	for (auto const& tile : movingTiles) {
		tile->update();
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	for (auto const& projectile : enemyProjectiles) {
		projectile->update();
	}

	// Collisions - Player, Enemy
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy) && enemy->state != game->stateDying) {
			player->loseLife();
			if (player->lifes <= 0) {
				init();
				return;
			}
		}
	}

	// Deletions - Projectile, Enemy
	list<CollectibleItem*> deleteItems;
	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<Projectile*> deleteEnemyProjectiles;
	list<Tile*> deleteTiles;

	for (auto const& enemy : enemies) {

		// Collision - Projectile, Enemy
		for (auto const& projectile : projectiles) {

			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				enemy->impacted();
				points++;
				textPoints->content = to_string(points);
				cout << "Enemy killed. Points: " << points << endl;

			}
		}
	}

	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	for (auto const& item : items) {
		if (player->isOverlap(item)) {
			bool iInList = find(deleteItems.begin(),
				deleteItems.end(), item) != deleteItems.end();
			if (!iInList) {
				deleteItems.push_back(item);
			}

			audioItem->play();
			collected++;
			textItems->content = to_string(collected);
			cout << "Item collected. Items: " << collected << endl;
		}
	}

	for (auto const& projectile : projectiles) {

		// Projectile traveledOut
		if (!projectile->isInRender(scrollX) || projectile->vx == 0) {
			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
				cout << "Projectile traveled out" << endl;
			}
			continue;
		}

		// Collision - Projectile, Tile
		for (auto const& tile : tiles) {
			if (tile->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				if (tile->isDestructible) {
					bool tInList = std::find(deleteTiles.begin(),
						deleteTiles.end(),
						tile) != deleteTiles.end();

					if (!tInList) {
						deleteTiles.push_back(tile);
					}
				}
			}
		}

	}

	for (auto const& projectile : enemyProjectiles) {
		// Collision EnemyProjectile and Player
		if (player->isOverlap(projectile)) {
			player->loseLife();
			if (player->lifes <= 0) {
				init();
				return;
			}
		}

		// Projectile traveledOut
		if (!projectile->isInRender(scrollX) || projectile->vx == 0) {
			bool pInList = std::find(deleteEnemyProjectiles.begin(),
				deleteEnemyProjectiles.end(),
				projectile) != deleteEnemyProjectiles.end();

			if (!pInList) {
				deleteEnemyProjectiles.push_back(projectile);
				cout << "Projectile traveled out" << endl;
			}
			continue;
		}

		// Collision - Projectile, Tile
		for (auto const& tile : tiles) {
			if (tile->isOverlap(projectile)) {
				bool pInList = std::find(deleteEnemyProjectiles.begin(),
					deleteEnemyProjectiles.end(),
					projectile) != deleteEnemyProjectiles.end();

				if (!pInList) {
					deleteEnemyProjectiles.push_back(projectile);
				}
			}
		}
	}

	// Deletion of enemies, items and projectiles
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
		delete delEnemy;
	}
	deleteEnemies.clear();

	for (auto const& delItem : deleteItems) {
		items.remove(delItem);
		delete delItem;
	}
	deleteItems.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delProjectile : deleteEnemyProjectiles) {
		enemyProjectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteEnemyProjectiles.clear();

	for (auto const& delTile : deleteTiles) {
		tiles.remove(delTile);
		space->removeStaticActor(delTile);
		delete delTile;
	}
	deleteTiles.clear();
}

void GameLayer::calculateScroll() {
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}

}

void GameLayer::draw() {
	calculateScroll();

	background->draw();

	for (auto const& tile : tiles) {
		tile->draw(scrollX);
	}
	for (auto const& tile : movingTiles) {
		tile->draw(scrollX);
	}
	for (auto const& item : items) {
		item->draw(scrollX);
	}
	player->draw(scrollX);

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX);
	}
	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX);
	}
	for (auto const& projectile : enemyProjectiles) {
		projectile->draw(scrollX);
	}

	cup->draw(scrollX);

	// HUD
	textPoints->draw();
	textItems->draw();
	backgroundPoints->draw();
	backgroundItems->draw();
	if (game->input == GameInputType::MOUSE) {
		buttonJump->draw();
		buttonShoot->draw();
		pad->draw();
	}

	SDL_RenderPresent(game->renderer);
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Movement
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
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

void GameLayer::mouseToControls(SDL_Event event) {
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = true;
			controlMoveX = pad->getOrientationX(motionX);
		}
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = true;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			controlMoveY = -1;
		}
	}
	if (event.type == SDL_MOUSEMOTION) {
		if (pad->clicked && pad->containsPoint(motionX, motionY)) {
			controlMoveX = pad->getOrientationX(motionX);
			if (controlMoveX > -20 && controlMoveX < 20) {
				controlMoveX = 0;
			}
		}
		else {
			controlMoveX = 0;
		}

		if (buttonShoot->containsPoint(motionX, motionY) == false) {
			controlShoot = false;
		}
		if (buttonJump->containsPoint(motionX, motionY) == false) {
			controlMoveY = 0;
		}

	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = false;
			controlMoveX = 0;
		}

		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = false;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			controlMoveY = 0;
		}

	}

}

void GameLayer::loadMap(string name) {
	char character = 'a';
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Error opening map file" << endl;
		return;
	}
	else {
		// For line
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Width of map in pixel
			// For each character (on each line)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character;			// Reads character
				cout << character;
				float x = 40 / 2 + j * 40;			// central  x
				float y = 32 + i * 32;				// floor y
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'E': {
		Enemy* enemy = new ShipEnemy(x, y, game);
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'T': {
		Enemy* enemy = new TrunkEnemy(x, y, game);
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1': {
		player = new Player(x, y, game);
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/bloque_tierra.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'U': {
		Tile* tile = new Tile("res/bloque_caja.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tile->isDestructible = true;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'X': {
		MovingTile* tile = new MovingTile("res/bloque_metal.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		movingTiles.push_back(tile);
		space->addDynamicActor(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'I': {
		CollectibleItem* item = new CollectibleItem(x, y, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		break;
	}
	case 'C': {
		cup = new Tile("res/copa.png", x, y, game);
		// modification to start counting from floor
		cup->y = cup->y - cup->height / 2;
		space->addDynamicActor(cup);
		break;
	}

	}
}

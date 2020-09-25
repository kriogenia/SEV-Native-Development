#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	init();
}

void GameLayer::init() {

	points = 0;

	delete background;
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);

	delete player;
	player = new Player(50, 50, game);

	delete backgroundPoints;
	backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);

	delete audioBackground;
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	bombs.clear();

	enemies.clear();
	enemies.push_back(new Enemy(300, 50, game));
	enemies.push_back(new Enemy(300, 200, game));

	enemyProjectiles.clear();

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
	background->update();

	// Enemy generation
	newEnemyTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		enemies.push_back(new Enemy(rX, rY, game));
		newEnemyTime = points*5 > 110 ? 10 : 110 - points*5;
	}

	//Bomb generation
	newBombTime--;
	if (newBombTime <= 0) {
		int rX = (rand() % (WIDTH - 50)) + 1 + 25;
		int rY = (rand() % (HEIGHT - 50)) + 1 + 25;
		bombs.push_back(new Bomb(rX, rY, game));
		cout << "Bomb spawned at " << rX << ", " << rY << endl;
		newBombTime = 500;
	}

	// Actors update
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
		if (!enemy->isOutOfRender() && enemy->x > player->x && enemy->x - player->x < 100) {
			auto projectile = enemy->autoshoot();
			if (projectile != NULL) {
				cout << "Enemy did shot" << endl;
				enemyProjectiles.push_back(projectile);
			}
		}
	}
	for (auto const& enemyProjectile : enemyProjectiles) {
		enemyProjectile->update();
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	// Collisions - Player, Enemy
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			init();
			return;
		}
	}

	// Deletions - Projectiles, Enemy, Bomb
	list<Enemy*> deleteEnemies;
	list<EnemyProjectile*> deleteEnemyProjectiles;
	list<Projectile*> deleteProjectiles;
	list<Bomb*> deleteBombs;

	// Collisions - Player, Bomb

	for (auto const& bomb : bombs) {
		if (player->isOverlap(bomb)) {
			bomb->explosionAudio->play();
			points += enemies.size();
			textPoints->content = to_string(points);
			enemies.clear();
			bool bInList = std::find(deleteBombs.begin(),
				deleteBombs.end(), bomb) != deleteBombs.end();
			if (!bInList) {
				deleteBombs.push_back(bomb);
				cout << "Bomb detonated" << endl;
			}
		}
	}

	for (auto const& enemyProjectile : enemyProjectiles) {
		// Collision - EnemyProjectile, Player
		if (player->isOverlap(enemyProjectile)) {
			init();
			return;
		}
		// EnemyProjectile traveled out
		if (enemyProjectile->isOutOfRender()) {
			bool pInList = std::find(deleteEnemyProjectiles.begin(),
				deleteEnemyProjectiles.end(),
				enemyProjectile) != deleteEnemyProjectiles.end();
			if (!pInList) {
				deleteEnemyProjectiles.push_back(enemyProjectile);
				cout << "Enemy projectile traveled out" << endl;
			}
		}
	}

	for (auto const& enemy : enemies) {

		// Enemy traveled out
		if (enemy->isOutOfRender()) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();
			if (!eInList) {
				deleteEnemies.push_back(enemy);
				cout << "Enemy traveled out" << endl;
			}
			continue;
		}

		// Collision - Projectile, Enemy
		for (auto const& projectile : projectiles) {

			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();

				if (!eInList) {
					deleteEnemies.push_back(enemy);
					points++;
					textPoints->content = to_string(points);
					cout << "Enemy killed. Points: " << points << endl;
				}

			}
		}
	}

	for (auto const& projectile : projectiles) {

		// Projectile traveled out
		if (projectile->isOutOfRender()) {
			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
				cout << "Projectile traveled out" << endl;
			}
			continue;
		}

	}

	// Deletion of bombs, enemies and projectiles
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		delete delEnemy;
	}
	deleteEnemies.clear();

	for (auto const& delEnemyProjectile : deleteEnemyProjectiles) {
		enemyProjectiles.remove(delEnemyProjectile);
		delete delEnemyProjectile;
	}
	deleteEnemyProjectiles.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delBomb : deleteBombs) {
		bombs.remove(delBomb);
		delete delBomb;
	}
	deleteBombs.clear();
}

void GameLayer::draw() {

	background->draw();
	player->draw();

	for (auto const& bomb : bombs) {
		bomb->draw();
	}
	for (auto const& enemy : enemies) {
		enemy->draw();
	}
	for (auto const& enemyProjectile : enemyProjectiles) {
		enemyProjectile->draw();
	}
	for (auto const& projectile : projectiles) {
		projectile->draw();
	}

	textPoints->draw();
	backgroundPoints->draw();

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
	if (event.type == SDL_QUIT) {
		game->loopActive = false;
	}


}

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
	backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * 0.9, HEIGHT * 0.05, 24, 24, game);
	textPoints = new Text("0", WIDTH * 0.9 + 25, HEIGHT * 0.05, game);
	textPoints->content = to_string(points);

	delete healthPoints;
	healthPoints = new Actor("res/corazon.png", 25, 25, 44, 36, game);
	textHealthPoints = new Text("3", 25 + 40, 25, game);
	textHealthPoints->content = to_string(player->hp);

	delete audioBackground;
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

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
		newEnemyTime = points*5 + 25 > 110 ? 25 : 110 - points*5;
	}

	// Item generation
	newItemTime--;
	if (newItemTime <= 0 && points >= 10) {
		int rX = (rand() % (WIDTH - 50)) + 1 + 25;
		int rY = (rand() % (HEIGHT - 50)) + 1 + 25;
		powerUps.push_back(new PowerUp(rX, rY, game));
		newItemTime = 300;
	}

	// Actors update
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
		if (!enemy->isOutOfRender() && enemy->x > player->x && enemy->x - player->x < 200) {
			auto projectile = enemy->autoshoot();
			if (projectile != NULL) {
				cout << "Enemy did shot from " << projectile->x << ", " << projectile->y << endl;
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

	// Deletions - Projectile, Enemy
	list<Enemy*> deleteEnemies;
	list<EnemyProjectile*> deleteEnemyProjectiles;
	list<PowerUp*> deletePowerUps;
	list<Projectile*> deleteProjectiles;

	// Collisions - Player, Enemy
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			player->hp--;
			player->audioDamage->play();
			textHealthPoints->content = to_string(player->hp);
			if (player->hp <= 0) {
				init();
				return;
			}
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();
			if (!eInList) {
				deleteEnemies.push_back(enemy);
				cout << "Enemy traveled out" << endl;
			}
		}
	}

	for (auto const& enemyProjectile : enemyProjectiles) {
		// Collision - EnemyProjectile, Player
		if (player->isOverlap(enemyProjectile)) {
			bool pInList = std::find(deleteEnemyProjectiles.begin(),
				deleteEnemyProjectiles.end(),
				enemyProjectile) != deleteEnemyProjectiles.end();

			if (!pInList) {
				deleteEnemyProjectiles.push_back(enemyProjectile);
			}

			player->hp--;
			player->audioDamage->play();
			textHealthPoints->content = to_string(player->hp);
			cout << "Contact! - HP: " << player->hp << endl;
			if (player->hp <= 0) {
				init();
				return;
			}
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

	// Collisions - Player, PowerUp
	for (auto const& powerUp : powerUps) {
		if (player->isOverlap(powerUp)) {
			bool pInList = std::find(deletePowerUps.begin(),
				deletePowerUps.end(),
				powerUp) != deletePowerUps.end();

			if (!pInList) {
				deletePowerUps.push_back(powerUp);
			}

			if (player->power == 1) {
				player->power = 2;
			}
			else {
				points++;
			}
			player->audioPowerUp->play();
			cout << "Player powered up" << endl;
		}
	}

	for (auto const& enemy : enemies) {

		// Enemy traveledOut
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

		// Projectile traveledOut
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

	// Deletion of enemies and projectiles
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

	for (auto const& delPowerUp : deletePowerUps) {
		powerUps.remove(delPowerUp);
		delete delPowerUp;
	}
	deletePowerUps.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();
}

void GameLayer::draw() {
	background->draw();
	player->draw();

	for (auto const& powerUp : powerUps) {
		powerUp->draw();
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
	textHealthPoints->draw();
	healthPoints->draw();

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
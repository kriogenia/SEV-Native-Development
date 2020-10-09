#pragma once

#include <iostream>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Layer.h"
class Layer;

using namespace std;

// Screen size constants
#define WIDTH 480
#define HEIGHT 320

enum class GameInputType {
	KEYBOARD, GAMEPAD, MOUSE
};

class Game
{
public:

	Game();

	void loop();
	void scale();

	SDL_Texture* getTexture(string filename);

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	Layer* layer;
	Layer* gameLayer;
	Layer* menuLayer;

	map<string, SDL_Texture*> mapTextures;

	bool loopActive;

	bool scaledToMax = false;
	float scaleLower = 1;

	int const stateMoving = 1;
	int const stateJumping = 2;
	int const stateDying = 3;
	int const stateDead = 4;
	int const stateShooting = 5;

	int const orientationRight = 1;
	int const orientationLeft = 2;

	int currentLevel = 0;
	int finalLevel = 2;

	GameInputType input  =GameInputType::KEYBOARD;

};

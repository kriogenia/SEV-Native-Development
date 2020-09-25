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
	Layer* gameLayer;

	map<string, SDL_Texture*> mapTextures; // map - cache

	bool loopActive;

	bool scaledToMax = false;
	float scaleLower = 1;

};

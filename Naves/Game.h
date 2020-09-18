#pragma once

#include <iostream>
#include <string>
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
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool loopActive;
	Layer* gameLayer;

};

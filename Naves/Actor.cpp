#include "Actor.h"

Actor::Actor(string filename, float x, float y, int width, int height, int fileWidth, int fileHeight) {
	this->game = game;
	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(game->renderer, surface);
	this-> x = x;
	this-> y = y;
	// File size
	this-> fileWidth = fileWidth;
	this-> fileHeight = fileHeight;
	// Game size
	this->width = width;
	this->height = height;
}

void Actor::draw() {
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth;
	source.h = fileHeight;

	SDL_Rect destination;
	destination.x = x - width / 2;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(game->renderer, texture, &source, &destination, 0, nullptr, SDL_FLIP_NONE);
}
#include "Actor.h"

Actor::Actor(string filename, float x, float y, int width, int height, Game* game) {
	this->game = game;
	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(game->renderer, surface);
	this-> x = x;
	this-> y = y;
	// File size
	this-> fileWidth = width;
	this-> fileHeight = height;
	// Game size
	this->width = width;
	this->height = height;
	// Speed
	this->vx = 0;
	this->vy = 0;
}

Actor::~Actor() {
	SDL_DestroyTexture(texture);
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

bool Actor::isOutOfRender() {
	return false;
}

bool Actor::isOverlap(Actor* actor) {
	bool overlap = false;
	if (actor->x - actor->width / 2 <= x + width / 2
		&& actor->x + actor->width / 2 >= x - width / 2
		&& actor->y + actor->height / 2 >= y - height / 2
		&& actor->y - actor->height / 2 <= y + height / 2) {
		overlap = true;
	}
	return overlap;
}

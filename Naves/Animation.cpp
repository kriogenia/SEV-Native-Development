#include "Animation.h"

Animation::Animation(string filename, float actorWidth, float actorHeight,
	float fileWidth, float fileHeight, int updateFrecuence, int totalFrames, Game* game) {

	// Load texture
	texture = game->getTexture(filename);

	this->actorWidth = actorWidth;
	this->actorHeight = actorHeight;
	this->fileWidth = fileWidth;
	this->fileHeight = fileHeight;
	this->updateFrecuence = updateFrecuence;
	this->totalFrames = totalFrames;
	this->game = game;

	updateTime = 0;			// last update
	currentFrame = 0;

	// Size of the frame to take
	frameWidth = fileWidth / totalFrames;
	frameHeight = fileHeight;

	// Rectangle to take
	source.x = 0;
	source.y = 0;
	source.w = frameWidth;
	source.h = frameHeight;
}

bool Animation::update() {
	updateTime++;
	if (updateTime > updateFrecuence) {
		updateTime = 0;
		currentFrame++;

		if (currentFrame >= totalFrames) {
			currentFrame = 0;
		}
	}

	source.x = currentFrame * frameWidth;
	return false;
}

void Animation::draw(float x, float y) {
	SDL_Rect destination;
	destination.x = x - actorWidth / 2;
	destination.y = y - actorHeight / 2;
	destination.w = actorWidth;
	destination.h = actorHeight;

	SDL_RenderCopyEx(game->renderer, texture, &source, &destination,
		0, NULL, SDL_FLIP_NONE);
}
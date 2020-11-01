#include "CollectibleItem.h"

CollectibleItem::CollectibleItem(float x, float y, Game* game) :
	Actor("res/icono_recolectable.png", x, y, 32, 32, game)
{
	this->animation = new Animation("res/recolectable.png", width, height,
		256, 32, 6, 8, true, game);
}

void CollectibleItem::draw(float scrollX) {
	animation->update();
	animation->draw(x - scrollX, y);
}

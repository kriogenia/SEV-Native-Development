#include "Space.h"

Space::Space(float gravity) {
	this->gravity = gravity;
	dynamicActors.clear();
	staticActors.clear();
}

void Space::addDynamicActor(Actor* actor) {
	dynamicActors.push_back(actor);
}

void Space::addStaticActor(Actor* actor) {
	staticActors.push_back(actor);
}

void Space::removeDynamicActor(Actor* actor) {
	dynamicActors.remove(actor);
}

void Space::removeStaticActor(Actor* actor) {
	staticActors.remove(actor);
}

void Space::update() {
	for (auto const& actor : dynamicActors) {
		actor->vy = actor->vy + gravity;
		// Max speed of falling
		if (actor->vy > 20) {
			actor->vy = 20;
		}

        // Aun no se han detectado choques
        actor->collisionDown = false;

		// Moving right / left
		updateMoveRight(actor);
		updateMoveLeft(actor);
        updateMoveTop(actor);
        updateMoveDown(actor);

	}
}

void Space::updateMoveRight(Actor* dynamicAct) {
    if (dynamicAct->vx > 0) {
        int possibleMovement = dynamicAct->vx;      // We start from the ideal movement

        int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;

        for (auto const& staticAct : staticActors) {

            int leftStatic = staticAct->x - staticAct->width / 2;
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;

            // Static element in the trayectory
            if ((rightDynamic + dynamicAct->vx) >= leftStatic
                && rightDynamic <= leftStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                // Check distance to the static is smaller than the speed movement
                if (possibleMovement >= leftStatic - rightDynamic) {
                    possibleMovement = leftStatic - rightDynamic;       // If so, adjust movement
                }
            }
        }

        dynamicAct->x = dynamicAct->x + possibleMovement;       // Updated movement
        dynamicAct->vx = possibleMovement;                      // Adjust speed
    }
}


void Space::updateMoveLeft(Actor* dynamicAct) {
    if (dynamicAct->vx < 0) {
        int possibleMovement = dynamicAct->vx;  // We start from the ideal movement

        int leftDynamic = dynamicAct->x - dynamicAct->width / 2;
        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;

        for (auto const& staticAct : staticActors) {

            int rightStatic = staticAct->x + staticAct->width / 2;
            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;

            // Static element in the trayectory
            if ((leftDynamic + dynamicAct->vx) <= rightStatic
                && leftDynamic >= rightStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                // Check distance to the static is smaller than the speed movement
                if (possibleMovement <= rightStatic - leftDynamic) {
                    possibleMovement = rightStatic - leftDynamic;   // If so, adjust movement
                }

            }

        }

        dynamicAct->x = dynamicAct->x + possibleMovement;
        dynamicAct->vx = possibleMovement;
    }
}

void Space::updateMoveDown(Actor* dynamicAct) {
    if (dynamicAct->vy > 0) {
        int possibleMovement = dynamicAct->vy;

        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;
        int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
        int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

        for (auto const& staticAct : staticActors) {

            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int leftStatic = staticAct->x - staticAct->width / 2;

            if ((downDynamic + dynamicAct->vy) >= topStatic
                && topDynamic < downStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {

                if (possibleMovement >= topStatic - downDynamic) {
                    possibleMovement = topStatic - downDynamic;
                    dynamicAct->collisionDown = true;
                }
            }
        }

        dynamicAct->y = dynamicAct->y + possibleMovement;
        dynamicAct->vy = possibleMovement;
    }
}

void Space::updateMoveTop(Actor* dynamicAct) {
    if (dynamicAct->vy < 0) {
        int possibleMovement = dynamicAct->vy;

        int topDynamic = dynamicAct->y - dynamicAct->height / 2;
        int downDynamic = dynamicAct->y + dynamicAct->height / 2;
        int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
        int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

        for (auto const& staticAct : staticActors) {

            int topStatic = staticAct->y - staticAct->height / 2;
            int downStatic = staticAct->y + staticAct->height / 2;
            int rightStatic = staticAct->x + staticAct->width / 2;
            int leftStatic = staticAct->x - staticAct->width / 2;

            if ((topDynamic + dynamicAct->vy) <= downStatic
                && downDynamic > topStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {

                if (possibleMovement <= downStatic - topDynamic) {
                    possibleMovement = downStatic - topDynamic;
                }
            }
        }

        dynamicAct->y = dynamicAct->y + possibleMovement;
        dynamicAct->vy = possibleMovement;
    }
}

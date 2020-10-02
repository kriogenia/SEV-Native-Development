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
		// Moving right / left
		updateMoveRight(actor);
		updateMoveLeft(actor);
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

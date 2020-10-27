#pragma once

#include "Actor.h"
#include "Background.h"
#include "Layer.h"

class MenuLayer :
    public Layer
{
public:
    MenuLayer(Game* game);

    void init() override;
    void draw() override;
    void processControls() override;
    void keysToControls(SDL_Event event);
    void mouseToControls(SDL_Event event);

    Background* background;
    Actor* button;

    bool controlContinue = false;


};


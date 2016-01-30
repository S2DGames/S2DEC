#pragma once

#include "Game.h"
#include "Wizard.h"

using namespace S2D;

void load(Game* game) {
	Entity& wizard = game->createEntity("Player");
	wizard.addComponent<Wizard>();
}

//change
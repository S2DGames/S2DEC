#pragma once

#include "Game.h"
#include "Wizard.h"

using namespace S2D;

void load(Game* game) {
	Entity& wizard = game->createEntity("Player");
	wizard.addComponent<Wizard>(sf::Vector2f{ game->SCREEN_SIZE.x/2.0f, game->SCREEN_SIZE.y/2.0f });
}

//change
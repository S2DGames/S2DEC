#pragma once

#include "Game.h"
#include "Ship.h"
#include "Gun.h"
#include "AlienCoordinator.h"

void loadSpaceInvaders(Game* game){
	int numAlienColumns = 11;
	float alienSpace = game->getSize().x * 0.85f;
	float border = (game->getSize().x - alienSpace) / 2.0f;
	float alienSpacing = alienSpace / numAlienColumns;

	Entity& ship = game->createEntity("ship");
	ship.addComponent<Ship>(game);
	ship.addComponent<Gun>(game);

	Entity& coordinator = game->createEntity("coordinator");
	AlienCoordinator& ac = coordinator.addComponent<AlienCoordinator>(game);
	ac.createAlien({game->getCameraRect().left + border, game->getCameraRect().top + 50});
}
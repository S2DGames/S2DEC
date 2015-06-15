#pragma once

#include "Game.h"
#include "Ship.h"
#include "Gun.h"
#include "AlienCoordinator.h"

void loadSpaceInvaders(Game* game){
	Entity& ship = game->createEntity("ship");
	ship.addComponent<Ship>(game);
	ship.addComponent<Gun>(game);

	Entity& coordinator = game->createEntity("coordinator");
	coordinator.addComponent<AlienCoordinator>(game);
}
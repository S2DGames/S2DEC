#pragma once

#include "Game.h"
#include "Screen.h"

using namespace S2D;

void load(Game* game){
	game->createEntity("screen").addComponent<Screen>();
}
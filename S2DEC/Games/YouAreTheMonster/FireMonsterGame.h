#include "Game.h"
#include "FireElemental.h"
#include "Background.h"

void loadFireMonsterGame(Game* game){
	Entity& playerEntity = game->createEntity("player");
	Component& player = playerEntity.addComponent<FireElemental>();
	
	Entity& background = game->createEntity("background");
	background.addComponent<Background>(dynamic_cast<FireElemental&>(player));
}
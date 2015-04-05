#pragma once

#include "Game.h"
#include "ShipPhysics.h"
#include "BulletPhysics.h"
#include "BulletImage.h"

using namespace S2D;

class Gun : public Component{
private:
	const int MAX_BULLET_COUNT = 10;
	
	Game* game{nullptr};
	ShipPhysics* shipPhysics;

public:
	Gun(Game* game) : game(game){

	}

	void init() override{
		if(owner->hasComponent<ShipPhysics>()){
			shipPhysics = &owner->getComponent<ShipPhysics>();
		}else{
			cerr << owner->getName() << ": ShipPhysics component missing" << endl;
		}
	}

	void spawn(){
		Entity& bullet = game->createEntity("bullet");
		bullet.addComponent<BulletPhysics>(game, shipPhysics->getPosition(), shipPhysics->getAngle());
		bullet.addComponent<BulletImage>("resources/bullet.png");
	}

	bool update(sf::Time frameTime) override{
		if(game->getKeyState(sf::Keyboard::Space) == KEY_PRESSED && game->getKeyState(sf::Keyboard::Space) != KEY_HELD){
			spawn();
		}
		return true;
	}
};
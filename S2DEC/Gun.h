#pragma once

#include "Game.h"
#include "ShipPhysics.h"
#include "BulletPhysics.h"
#include "BulletImage.h"

using namespace S2D;

class Gun : public Component{
private:
	Game* game{nullptr};
	ShipPhysics* shipPhysics;


	const int rateOfFire = 12; //10 frames for 1 bullet

	int frameCount = 0;
	bool count = false;
	bool readyToFire = true;
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
		bullet.addComponent<BulletPhysics>(game, shipPhysics->getPosition(), shipPhysics->getAngle() * DEGTORAD, shipPhysics);
		bullet.addComponent<BulletImage>("resources/bullet.png");
		bullet.onStart();
		bullet.setZ(-1);
	}

	bool update(sf::Time frameTime) override{
		if(readyToFire && ((game->getKeyState(sf::Keyboard::Space) == KEY_PRESSED))){
			spawn();
			readyToFire = false;
			count = true;
		}
		if(count){
			if(frameCount > rateOfFire){
				frameCount = 0;
				count = false;
				readyToFire = true;
			}
			frameCount++;
		}
		return true;
	}
};
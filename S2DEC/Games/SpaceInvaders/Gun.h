#pragma once

#include "Game.h"
#include "Ship.h"
#include "Bullet.h"

using namespace S2D;

class Gun : public Component{
private:
	Game* game{nullptr};
	Ship* ship;


	const int rateOfFire = 12; //10 frames for 1 bullet

	int frameCount = 0;
	bool count = false;
	bool readyToFire = true;
public:
	Gun(Game* game) : game(game){

	}

	void init() override{
		if(owner->hasComponent<Ship>()){
			ship = &owner->getComponent<Ship>();
		}else{
			cerr << owner->getName() << ": Ship component missing" << endl;
		}
	}

	void spawn(){
		Entity& bullet = game->createEntity("bullet");
		bullet.addComponent<Bullet>(game, ship, "resources/bullet.png");
		bullet.onStart();
		bullet.setZ(-1);
	}

	void update(float frameTime) override{
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
	}
};
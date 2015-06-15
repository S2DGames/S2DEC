#pragma once

#include <sstream>
#include "Game.h"
#include "Alien.h"

using std::stringstream;
using namespace S2D;

class AlienCoordinator : public Component{
private:
	Game* game{nullptr};
	vector<Entity*> aliens;
	int count = 0;

public:
	AlienCoordinator(Game* game) : game(game){

	}

	void createAlien(sf::Vector2f startingPosition){
		stringstream ss;
		ss << "alien " << count;
		//create an entity to contain this alien
		aliens.push_back(&(game->createEntity(ss.str())));
		//create the alien component
		aliens[count]->addComponent<Alien>(game, startingPosition);
		count++;
	}

	void init() override{

	}

	void update(float frameTime) override{
		
	}
};
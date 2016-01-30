#pragma once
#include "AlienCoordinator.h"
#include "Alien.h"

AlienCoordinator::AlienCoordinator(Game* game) : game(game){

}

void AlienCoordinator::createAlien(sf::Vector2f startingPosition){
	stringstream ss;
	ss << "alien " << count;
	//create an entity to contain this alien
	alienEntities[count] = &(game->createEntity(ss.str()));
	//create the alien component
	aliens[count] = &(alienEntities[count]->addComponent<Alien>(game, this, count, startingPosition));
	count++;
}

void AlienCoordinator::update(float frameTime){
	frameCount++;
	if(frameCount > 30){
		for(Alien* a : aliens){
			if(a != nullptr){
				sf::Vector2f currentPos = a->getsfPosition();
				a->setNextPosition({currentPos.x - a->getsfSize().x, currentPos.y});
			}
		}
		frameCount = 0;
	}
}

void AlienCoordinator::removeAlien(int id){
	alienEntities[id] = nullptr;
	aliens[id] = nullptr;
}
#pragma once

#include <sstream>
#include "Game.h"

using std::stringstream;
using namespace S2D;

class Alien;

class AlienCoordinator : public Component{
private:
	Game* game{nullptr};
	array<Entity*, 22> alienEntities;
	array<Alien*, 22> aliens;
	int count = 0;

	float frameCount = 0;
public:
	AlienCoordinator(Game* game);
	void createAlien(sf::Vector2f startingPosition);
	void update(float frameTime) override;
	void removeAlien(int id);
};
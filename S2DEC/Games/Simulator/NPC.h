#pragma once

#include "SFML/System/Vector2.hpp"

using namespace S2D;

class NPC{
public:
	virtual bool moveTowardsPoint_Direct(sf::Vector2f destination){
		return false;
	}

	virtual bool moveTowardsPoint(sf::Vector2f& destination){
		return false;
	}

	virtual bool moveTowardsArea(sf::FloatRect destination){
		return false;
	}
};
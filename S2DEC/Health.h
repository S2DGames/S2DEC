#pragma once

#include "Component.h"

using namespace S2D;

class Health : public Component{
private:
	int health = 1;

public:
	Health(int maxHP){
		health = maxHP;
	}

	int getHealth(){
		return health;
	}

	void setHealth(int value){
		health = value;
	}

	void damage(int value){
		health -= value;
	}

	void update(sf::Time frameTime) override {
		if (health <= 0){
			owner->destroy();
		}
	}
};
#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"

using namespace S2D;

class EnemySpawner : public Component {
private:
	int maxEnemyCount = 1;

	int enemyCount = 0;
	
public:
	EnemySpawner() {
		
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override {
		
	}

	//change

	/**
	* Called when the Game starts.
	*/
	void onStart() override {

	}

	/**
	* Called once every frame.
	*/
	void update(float frameTime) override {
		
	}
};
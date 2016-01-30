#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "Enemy.h"

using namespace S2D;

class EnemySpawner : public Component {
private:
	int maxEnemyCount = 1;
	int enemyCount = 0;

	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	std::uniform_int_distribution<int> fromDist;

	float totalFrameTime = 0.0f;
	
public:
	EnemySpawner() {

	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override {
		xDist = std::uniform_int_distribution<int>(0, game->getSize().x);
		yDist = std::uniform_int_distribution<int>(0, game->getSize().y);
		fromDist = std::uniform_int_distribution<int>(1, 4);
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
		totalFrameTime += frameTime;

		if (totalFrameTime > 2.0f) {
			spawnEnemy();
			totalFrameTime = 0.0f;
		}
	}

	void spawnEnemy() {
		sf::Vector2f startPosition{0.0f, 0.0f};
		switch (game->getRandomInt(fromDist)) {
		case 1:
			//left;
			startPosition.y = (float)game->getRandomInt(yDist);
			break;
		case 2:
			startPosition.y = (float)game->getRandomInt(yDist);
			startPosition.x = game->getSize().x;
			break;
		case 3:
			startPosition.x = (float)game->getRandomInt(xDist);
			break;
		case 4:
			startPosition.x = (float)game->getRandomInt(xDist);
			startPosition.y = game->getSize().y;
			break;
		}
		game->createEntity("Enemy").addComponent<Enemy>(startPosition, sf::Vector2f{ game->getSize().x / 2.0f, game->getSize().y / 2.0f }, (void*)this);
		enemyCount++;
	}

	void enemyDied() {
		enemyCount--;
	}
};
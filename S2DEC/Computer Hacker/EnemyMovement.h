#pragma once

#include "Game.h"

class EnemyPhysics;
using namespace S2D;

enum Behavior{ stand, patrol, moveToPlayer };

class EnemyMovement : public Component{
private:
	Behavior currentBehavior;
	Game* game{ nullptr };

	float speed = 1.0f;
	int direction;
	sf::Vector2f spawnPoint;
	sf::Vector2f patrolStart;
	sf::Vector2f patrolEnd;

	EnemyPhysics* enemyPhysics{ nullptr };

public:
	EnemyMovement(Game* game, Behavior behavior, sf::Vector2f spawn);
	EnemyMovement(Game* game, Behavior behavior, sf::Vector2f patrolStart, sf::Vector2f patrolEnd);
	void init() override;
	void onStart() override;
	void update(sf::Time frameTime) override;

	float getVelocity() const;
	sf::Vector2f getSpawn() const;

	void setSpeed(float newSpeed);
	void setPatrol(sf::Vector2f start, sf::Vector2f end);
	void setPatrolStart(sf::Vector2f startPoint);
	void setPatrolEnd(sf::Vector2f endPoint);
};
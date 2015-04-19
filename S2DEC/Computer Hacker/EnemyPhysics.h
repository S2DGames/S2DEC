#pragma once
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "EnemyMovement.h"
#include "Component.h"
#include "Game.h"

class HackerPhysics;
class ComputerAttack;
using namespace S2D;

class EnemyPhysics : public Component{
private:
	Game* game{ nullptr };
	b2Body* body{ nullptr };
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	EnemyMovement* enemyMovement;
	sf::Vector2f position;
	bool onGround;

public:
	EnemyPhysics(Game* game);
	~EnemyPhysics();
	void init() override;
	void onStart() override;
	void update(sf::Time frameTime) override;
	void beginCollision(Component* component, b2Contact* contact) override;
	void endCollision(Component* component, b2Contact* contact) override;
	void jump();
	float getVelocity(){
		return enemyMovement->getVelocity(); 
	}

	sf::Vector2f getPosition();

};
#pragma once

#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Game.h"
#include "ShipControls.h"

using namespace S2D;

class ShipImage;

class ShipPhysics : public Component{
private:
	ShipControls* shipControls{nullptr};
	b2World* world{nullptr};
	b2Body* body{nullptr};
	sf::RenderWindow& window;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2CircleShape shape;
	sf::View view;

	float maxSpeed = 10.0f;

public:
	ShipPhysics(Game* game);

	void init() override;

	void onStart() override;

	bool update(sf::Time frameTime) override;

	void beginCollision(Component* collidedComponent, b2Contact* contact) override;

	void endCollision(Component* collidedComponent, b2Contact* contact) override;

	sf::Vector2f getPosition() const;

	float getAngle() const;
};
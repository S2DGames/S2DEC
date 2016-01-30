#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Common/b2Math.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"

using namespace S2D;

class Enemy : public Component {
private:
	sf::RectangleShape image;

	b2Body* body{ nullptr };
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{ nullptr };

	vector<sf::Keyboard::Key> playerKeyPresses;

	b2Vec2 velocity;
	sf::Vector2f endPosition;

public:
	Enemy(sf::Vector2f position, sf::Vector2f endPosition) : endPosition(endPosition){
		image.setSize(sf::Vector2f(20.0f, 20.0f));
		image.setOrigin((image.getSize().x) / 2.0f, (image.getSize().y) / 2.0f);
		image.setPosition(position);
		bodyDef.position = { sfTob2(position) };
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override {
		bodyDef.type = b2_dynamicBody;

		shape.SetAsBox(sfTob2(image.getSize().x / 2.0f), sfTob2(image.getSize().y / 2.0f));
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
		fixture->SetSensor(true);
		movesfTob2(image, body);

		float xDistance = sfTob2(endPosition.x - image.getPosition().x);
		float yDistance = sfTob2(endPosition.y - image.getPosition().y);
		float hDistance = sqrt(pow(xDistance, 2.0f) + pow(yDistance, 2.0f));
		float speed = 0.5f;
		float step = speed / hDistance;
		b2Vec2 velocity = { step * xDistance, step * yDistance };
		body->SetLinearVelocity(velocity);
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

		movesfTob2(image, body);
	}

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override {
		target.draw(image);
	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	* Do not delete or add physics objects in the scope of this function.
	*/
	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	* Do not delete or add physics objects in the scope of this function.
	*/
	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}
};
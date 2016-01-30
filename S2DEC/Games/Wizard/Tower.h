#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"

using namespace S2D;

class Tower : public Component {
private:
	sf::CircleShape image;

	b2Body* body{ nullptr };
	b2BodyDef bodyDef;
	b2CircleShape shape;
	b2Fixture* fixture{ nullptr };

public:
	Tower(sf::Vector2f position) {
		image.setRadius(25.0f);
		image.setPosition(position);
		image.setOrigin(image.getRadius(), image.getRadius());
		bodyDef.position = { sfTob2(position) };
	}

	void init() override {
	bodyDef.type = b2_dynamicBody;

	shape.m_radius = sfTob2(image.getRadius());
	body = game->CreateBody(&bodyDef);
	body->SetUserData(this);
	body->SetFixedRotation(true);
	fixture = body->CreateFixture(&shape, 1.0f);
	fixture->SetFriction(0.0f);
	fixture->SetRestitution(1.0f);
	movesfTob2(image, body);
	}

	void update(float frameTime) override {

	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void draw(sf::RenderTarget& target) override {
		target.draw(image);
	}
};
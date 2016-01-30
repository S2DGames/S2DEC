#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "WizardUtility.h"

using namespace S2D;

class Spell : public Component {
protected:
	sf::Vector2f startPos;
	sf::RectangleShape image;

private:

	b2Body* body{ nullptr };
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{ nullptr };
	sf::Vector2f endPosition;
	
	SpellType spellType;

public:
	Spell(sf::Vector2f position, sf::Vector2f endPosition, SpellType type) {
		startPos = position;
		image.setSize(sf::Vector2f(20.0f, 20.0f));
		image.setPosition(startPos);
		image.setOrigin((image.getSize().x) / 2.0f, (image.getSize().y) / 2.0f);
		bodyDef.position = { sfTob2(startPos) };
		this->endPosition = endPosition;
		spellType = type;
	}

	virtual void init() override {
		bodyDef.type = b2_dynamicBody;

		shape.SetAsBox(sfTob2(image.getSize().x / 2.0f), sfTob2(image.getSize().y / 2.0f));
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
		movesfTob2(image, body);

		float speed = 1.5f;

		if (spellType == SpellType::Fire) {
			speed = 1.5f;
		}
		else if (spellType == SpellType::Water) {
			speed = 1.5f;
		}
		else if (spellType == SpellType::Lightning) {
			speed = 1.5f;
		}

		float xDistance = sfTob2(endPosition.x - image.getPosition().x);
		float yDistance = sfTob2(endPosition.y - image.getPosition().y);
		float hDistance = sqrt(pow(xDistance, 2.0f) + pow(yDistance, 2.0f));

		float step = speed / hDistance;
		b2Vec2 velocity = { step * xDistance, step * yDistance };
		body->SetLinearVelocity(velocity);
	}

	virtual void update(float frameTime) override {
		if (image.getPosition().x > (endPosition.x - 5) && image.getPosition().x < (endPosition.x + 5) &&
			image.getPosition().y >(endPosition.y - 5) && image.getPosition().y < (endPosition.y + 5) &&
			spellType != SpellType::Lightning) {
			game->DestroyBody(body);
			this->owner->destroy();
		}
		movesfTob2(image, body);
	}

	virtual void draw(sf::RenderTarget& target) override {
		target.draw(image);
	}

	virtual void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	virtual void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}
};
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
	bool destroySpell = false;

private:
	bool isAlive = true;
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
		if (type == SpellType::Fire) {
			image.setFillColor(sf::Color::Red);
		}
		else if (type == SpellType::Water) {
			image.setFillColor(sf::Color::Blue);
		} 
		else if (type == SpellType::Lightning) {
			image.setFillColor(sf::Color::Yellow);
		}
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
		movesfTob2(image, body);
		//destroy if offscreen
		if (destroySpell && isAlive) {
			DestroySpell();
		}
	}

	virtual void draw(sf::RenderTarget& target) override {
		if (isAlive) {
			target.draw(image);
		}
	}

	virtual void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	virtual void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void DestroySpell() {
		game->DestroyBody(body);
		//this->owner->destroy();
		isAlive = false;
	}

	void setDestroySpell(bool flag) {
		destroySpell = flag;
	}
};
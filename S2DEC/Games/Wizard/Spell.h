#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "WizardUtility.h"

using namespace S2D;

class Spell : public Component {
private:
	sf::RectangleShape image;

	b2Body* body{ nullptr };
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{ nullptr };
	sf::Vector2f endPosition;

	
	SpellType spellType;

public:
	Spell(sf::Vector2f position, sf::Vector2f endPosition, SpellType type) {
		image.setSize(sf::Vector2f(20.0f, 20.0f));
		image.setPosition(position);
		image.setOrigin((image.getSize().x) / 2.0f, (image.getSize().y) / 2.0f);
		bodyDef.position = { sfTob2(position) };
		this->endPosition = endPosition;
		spellType = type;
	}

	void init() override {
		bodyDef.type = b2_dynamicBody;

		shape.SetAsBox(sfTob2(image.getSize().x / 2.0f), sfTob2(image.getSize().y / 2.0f));
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
		movesfTob2(image, body);

		if (spellType == SpellType::Fire) {
			body->SetLinearVelocity({ sfTob2(endPosition.x - image.getPosition().x), sfTob2(endPosition.y - image.getPosition().y) });
		}
		else if (spellType == SpellType::Water) {
			body->SetLinearVelocity({ sfTob2(endPosition.x - image.getPosition().x) * 2.0f, sfTob2(endPosition.y - image.getPosition().y) * 2.0f });
		}
		else if (spellType == SpellType::Lightning) {
			body->SetLinearVelocity({ sfTob2(endPosition.x - image.getPosition().x) * 2.0f, sfTob2(endPosition.y - image.getPosition().y) * 2.0f });
		}
		//TODO calculate velocity for the X and Y to reach destination based on the spell
	}

	void update(float frameTime) override {
		if (image.getPosition().x > (endPosition.x - 5) && image.getPosition().x < (endPosition.x + 5) &&
			image.getPosition().y >(endPosition.y - 5) && image.getPosition().y < (endPosition.y + 5) &&
			spellType != SpellType::Lightning) {
			game->DestroyBody(body);
			this->owner->destroy();
		}
		movesfTob2(image, body);
	}

	void draw(sf::RenderTarget& target) override {
		target.draw(image);
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}
};
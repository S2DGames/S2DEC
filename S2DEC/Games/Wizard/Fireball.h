#include "Spell.h"
#include "WizardUtility.h"
#include "Enemy.h"

using namespace S2D;

class Fireball : public Spell {
private:
	sf::CircleShape image;

	b2Body* body{ nullptr };
	b2BodyDef bodyDef;
	b2CircleShape shape;
	b2Fixture* fixture{ nullptr };
public:
	Fireball(sf::Vector2f position, sf::Vector2f endPosition): Spell(position, endPosition, SpellType::Fire ) {

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

	virtual void draw(sf::RenderTarget& target) override {
		target.draw(image);
	}

	void createExplosion() {
		image.getPosition();
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {
		if (auto enemy = dynamic_cast<Enemy*>(collidedComponent)) {
			createExplosion();
		}
	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}
};
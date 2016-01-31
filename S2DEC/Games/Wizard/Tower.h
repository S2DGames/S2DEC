#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "Enemy.h"

using namespace S2D;

class Tower : public Component {
private:
	sf::CircleShape image;
	sf::CircleShape explosion;

	b2Body* body{ nullptr };
	b2BodyDef bodyDef;
	b2CircleShape shape;
	b2Fixture* fixture{ nullptr };

	sf::Vector2f position;

	int health = 10;
	bool isGrowing = false;
	bool drawTower = true;
public:
	Tower(sf::Vector2f position) {
		this->position = position;
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
		fixture->SetSensor(true);
		movesfTob2(image, body);
	}

	void update(float frameTime) override {
		if (health == 0) {
			createExplosion();
		}
		if (isGrowing) {
			if (explosion.getRadius() < 100.0f) {
				explosion.setRadius(explosion.getRadius() + .5f);
				explosion.setOrigin(explosion.getRadius(), explosion.getRadius());
			}
			else {
				isGrowing = false;
			}
		}
		else {
			if (explosion.getRadius() >= 0) {
				explosion.setRadius(explosion.getRadius() - .1f);
				explosion.setOrigin(explosion.getRadius(), explosion.getRadius());
			}
			if (explosion.getRadius() < 1 && explosion.getRadius() > 0) {
				if (body != nullptr) {
					game->DestroyBody(body);
				}
				game->endScene();
				owner->destroy();
			}
		}
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {
		if (auto enemy = dynamic_cast<Enemy*>(collidedComponent)) {
			health--;
			enemy->setDestroy(true);
		}
	}

	void createExplosion() {
		isGrowing = true;
		drawTower = false;
		explosion.setRadius(10.0f);
		explosion.setPosition(position);
		explosion.setOrigin(explosion.getRadius(), explosion.getRadius());
	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void draw(sf::RenderTarget& target) override {
		if (drawTower) {
			target.draw(image);
		}
		target.draw(explosion);
	}

	int getHealth() {
		return health;
	}
};
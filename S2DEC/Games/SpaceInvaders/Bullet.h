#pragma once

#include <iostream>
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "Ship.h"

using std::cout;
using std::endl;
using namespace S2D;

class Bullet : public Component{
private:
	Game* game{nullptr};
	Ship* ship{nullptr};
	b2Body* body{nullptr};
	b2BodyDef bodyDef;
	b2CircleShape shape;
	b2Fixture* fixture{nullptr};

	sf::CircleShape image;

	float maxSpeed = 12.0f;

	sf::FloatRect cameraRect;

public:
	Bullet(Game* game, Ship* ship, string filename) : game(game), ship(ship){
		bodyDef.type = b2_dynamicBody;
		shape.m_radius = 5.0f / SCALE;
		image.setRadius(5);
		image.setOrigin(image.getRadius(), image.getRadius());
		cout << "bullet created" << endl;
	}

	~Bullet(){
		game->DestroyBody(body);
	}

	void init() override{
		bodyDef.position = ship->getb2Position();
		image.setPosition(bodyDef.position.x * SCALE, bodyDef.position.y * SCALE);
		body = game->CreateBody(&bodyDef);
		fixture = body->CreateFixture(&shape, 0.1f);
		fixture->SetSensor(true);
		body->SetUserData(this);
		body->SetLinearVelocity({0, -maxSpeed});
	}

	void onStart() override{
		cameraRect = game->getCameraRect();
	}

	void update(float frameTime) override{
		if(!cameraRect.contains(getPosition())){
			owner->destroy();
		}

		movesfTob2(&image, body);
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(image);
	}

	sf::Vector2f getPosition(){
		return {body->GetPosition().x * SCALE, body->GetPosition().y * SCALE};
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override{

	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override{

	}
};
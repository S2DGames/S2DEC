#pragma once

#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Game.h"
#include "Util.h"

using namespace S2D;

class BulletPhysics : public Component{
private:
	b2Body* body{nullptr};
	sf::RenderWindow& window;
	b2BodyDef bodyDef;
	b2CircleShape shape;

	sf::Vector2f initialPosition;
	float angle;

	float maxSpeed = 20.0f;

	float sin;
	float cos;

public:
	BulletPhysics(Game* game, sf::Vector2f position, float angle) : window(*game), initialPosition(position), angle(angle){
		bodyDef.type = b2_dynamicBody;
		bodyDef.angle = angle * (float)DEGTORAD;
		bodyDef.position = {position.x / SCALE, position.y / SCALE};
		shape.m_radius = 1.0f;
		body = game->CreateBody(&bodyDef);
		body->CreateFixture(&shape, 0.1f);
		sin = std::sin(angle);
		cos = std::cos(angle);
	}

	bool update(sf::Time frameTime) override{
		sf::Vector2f cameraPosition = {window.getView().getCenter().x - (window.getSize().x / 2.0f), window.getView().getCenter().y - (window.getSize().y / 2.0f)};
		sf::FloatRect viewRect = {cameraPosition.x,
								  cameraPosition.y,
								  (float)window.getSize().x,
								  (float)window.getSize().y};
		if(!viewRect.contains(getPosition())){
			//owner->destroy();
		}
		body->SetLinearVelocity({maxSpeed * sin / SCALE, -maxSpeed * cos / SCALE});
		return true;
	}

	sf::Vector2f getPosition(){
		return {body->GetPosition().x * SCALE, body->GetPosition().y * SCALE};
	}

	float getAngle(){
		return (float)(body->GetAngle() * RADTODEG);
	}
};
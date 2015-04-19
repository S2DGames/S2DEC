#pragma once

#include "Component.h"
#include "Game.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/Joints/b2RevoluteJoint.h"
#include "HackerPhysics.h"

using namespace S2D;

class ComputerAttack : public Component{
private:
	Game* game;
	
	b2Body* body;
	b2BodyDef bodyDef;
	b2Fixture* fixture;
	b2PolygonShape rectangleShape;
	b2RevoluteJointDef jointDef; 
	b2Joint* joint;

	HackerPhysics* hackerPhysics;

	sf::RectangleShape rs;

	bool attacking = false;
	float attackTime = 0.0f;
	bool recharging = false;

public:
	ComputerAttack(Game* game) : game(game){
		bodyDef.type = b2_dynamicBody;
	}

	~ComputerAttack(){
		game->DestroyBody(body);
	}

	void init() override{
		if(owner->hasComponent<HackerPhysics>()){
			hackerPhysics = &owner->getComponent<HackerPhysics>();
		}
	}

	void onStart() override{
		bodyDef.position = {(hackerPhysics->getPosition().x + 10.0f) / SCALE, (hackerPhysics->getPosition().y - 10.0f) / SCALE};
		body = game->CreateBody(&bodyDef);
		rectangleShape.SetAsBox(25.0f / SCALE / 2.0f, 25.0f / SCALE / 2.0f);
		fixture = body->CreateFixture(&rectangleShape, 1.0f);
		jointDef.bodyA = body;
		jointDef.bodyB = hackerPhysics->getBody();
		jointDef.collideConnected = false;
		jointDef.localAnchorA.Set(10.0f / SCALE, -10.0f / SCALE);
		jointDef.localAnchorB.Set(10.0f / SCALE, -30.0f / SCALE);
		joint = game->CreateJoint(&jointDef);
		rs.setSize({25, 25});
		rs.setOrigin(25 / 2.0f, 25 / 2.0f);
		rs.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		rs.setRotation(body->GetAngle() * RADTODEG);
	}

	void update(sf::Time frametime) override{
		rs.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		rs.setRotation(body->GetAngle() * RADTODEG);

		if(game->getMouseState(sf::Mouse::Left) == KEY_PRESSED && !attacking){
			//body->ApplyAngularImpulse(body->GetMass() / SCALE, true);
			body->SetAngularVelocity(5);
			attacking = true;
		}

		if(attacking){
			attackTime += frametime.asSeconds();
			if(recharging && attackTime >= 1){
				attacking = false;
				recharging = false;
				attackTime = 0.0f;
				body->SetAngularVelocity(0);
			}
			if(attackTime >= .5 && !recharging){
				body->SetAngularVelocity(-5);
				recharging = true;
			}
		}

	}

	void draw(sf::RenderTarget& target) override{
		target.draw(rs);
	}

};
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
	b2RevoluteJoint* rJoint;

	HackerPhysics* hackerPhysics;

	enum{Left = -1, Right = 1};

	sf::Sprite sprite;
	sf::Texture* idleTexture;

	bool attacking = false;
	float attackTime = 0.0f;
	bool recharging = false;

	int direction = 1;

	sf::IntRect textureRect{0, 0, 0, 0};
	float animationFrameTimeCount = 0.0f;

public:
	ComputerAttack(Game* game) : game(game), idleTexture(game->loadTexture("resources/idleComputerAnimation.png", true)){
		bodyDef.type = b2_dynamicBody;
		sprite.setTexture(*idleTexture);
		textureRect = {0, 0, 26, 36};
		sprite.setTextureRect(textureRect);
		sprite.setOrigin(26 / 2.0f, 36 / 2.0f);
		sprite.setScale({2, 2});
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
		bodyDef.position = {(hackerPhysics->getPosition().x - 90.0f) / SCALE, (hackerPhysics->getPosition().y - 20.0f) / SCALE};
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		rectangleShape.SetAsBox(26.0f / SCALE, 36.0 / SCALE);
		fixture = body->CreateFixture(&rectangleShape, 1.0f);
		jointDef.bodyA = body;
		jointDef.bodyB = hackerPhysics->getBody();
		jointDef.collideConnected = false;
		jointDef.localAnchorA.Set(70.0f / SCALE, -10.0f / SCALE);
		jointDef.localAnchorB.Set(-25.0f / SCALE, -50.0f / SCALE);
		jointDef.enableLimit = true;
		jointDef.lowerAngle = 125 * DEGTORAD;
		jointDef.upperAngle = 270 * DEGTORAD;
		jointDef.enableMotor = true;
		jointDef.maxMotorTorque = 50;
		jointDef.motorSpeed = 360 * DEGTORAD;

		joint = game->CreateJoint(&jointDef);
		rJoint = (b2RevoluteJoint*)joint;
		
		sprite.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		sprite.setRotation(body->GetAngle() * RADTODEG);
	}

	void update(sf::Time frametime) override{
		sprite.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		sprite.setRotation(body->GetAngle() * RADTODEG);

		if(game->getKeyState(sf::Keyboard::Z) == KEY_PRESSED && !attacking){
			if(direction == 1){
				rJoint->SetMotorSpeed(-1080 * DEGTORAD * direction);
			} else{
				rJoint->SetMotorSpeed(1080 * DEGTORAD);
			}
			attacking = true;
		}

		if(direction == 1 && rJoint->GetJointAngle() <= rJoint->GetLowerLimit()){
			rJoint->SetMotorSpeed(360 * DEGTORAD * direction);
		}

		if(direction == -1 && rJoint->GetJointAngle() >= rJoint->GetUpperLimit()){
			rJoint->SetMotorSpeed(-360 * DEGTORAD);

		}

		if(direction == 1 && rJoint->GetJointAngle() >= rJoint->GetUpperLimit() && attacking){
			attacking = false;
		}

		if(direction == -1 && rJoint->GetJointAngle() <= rJoint->GetLowerLimit() && attacking){
			attacking = false;
		}

		if(game->getKeyState(sf::Keyboard::Left)){
			if(direction == 1){
				left();
			}
			direction = -1;
		}

		if(game->getKeyState(sf::Keyboard::Right)){
			if(direction == -1){
				right();
			}
			direction = 1;
		}

		animationFrameTimeCount += frametime.asMilliseconds();
		if(animationFrameTimeCount >= 16){
			textureRect = {textureRect.left + 26, textureRect.top, textureRect.width, textureRect.height};
			if(textureRect.left >= idleTexture->getSize().x){
				textureRect.left = 0;
			}
			animationFrameTimeCount = 0.0f;
			sprite.setTextureRect(textureRect);
		}

	}

	void left(){
		float currentSpeed = rJoint->GetMotorSpeed();
		float currentAngle = rJoint->GetJointAngle();
		game->DestroyJoint(joint);

		jointDef.localAnchorA.Set(-70.0f / SCALE, -10.0f / SCALE);
		jointDef.localAnchorB.Set(25.0f / SCALE, -50.0f / SCALE);
		jointDef.lowerAngle = 90 * DEGTORAD;
		jointDef.upperAngle = 270 * DEGTORAD;
		jointDef.maxMotorTorque = 50;
		jointDef.motorSpeed = -currentSpeed;

		joint = game->CreateJoint(&jointDef);
		rJoint = (b2RevoluteJoint*)joint;
	}

	void right(){
		float currentSpeed = rJoint->GetMotorSpeed();
		float currentAngle = rJoint->GetJointAngle();
		game->DestroyJoint(joint);

		jointDef.localAnchorA.Set(70.0f / SCALE, -10.0f / SCALE);
		jointDef.localAnchorB.Set(-25.0f / SCALE, -50.0f / SCALE);
		jointDef.lowerAngle = 150 * DEGTORAD;
		jointDef.upperAngle = 270 * DEGTORAD;
		jointDef.maxMotorTorque = 50;
		jointDef.motorSpeed = -currentSpeed;

		joint = game->CreateJoint(&jointDef);
		rJoint = (b2RevoluteJoint*)joint;
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(sprite);
	}

	int getDirection(){
		return direction;
	}

	void beginCollision(Component* component, b2Contact* contact) override{
		rJoint->SetMotorSpeed(360 * DEGTORAD * direction);
	}

};
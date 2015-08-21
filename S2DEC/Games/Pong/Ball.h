#pragma once
#include <random>
#include <chrono>
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "Component.h"
#include "Game.h"
#include "Paddle.h"
#include "Boundaries.h"
#include "Score.h"

using std::default_random_engine;
using std::uniform_int_distribution;
using std::chrono::system_clock;
using std::bind;
using namespace S2D;

class Ball : public Component{
private:
	b2Body* body{nullptr};
	b2BodyDef bodyDef;
	b2CircleShape shape;
	b2Fixture* fixture{nullptr};

	sf::CircleShape image;

	float speed = 4.0f;

	Score* score{nullptr};

	Paddle* leftPaddle;
	Paddle* rightPaddle;

	bool respawnBall;

	default_random_engine rng;

	std::shared_ptr<ltbl::LightShape> lightShape;

public:
	//pass in the Score component and both Paddle components to do game logic later on
	Ball(sf::Vector2f startingPosition, Score* score, Paddle* leftPaddle, Paddle* rightPaddle) : score(score), leftPaddle(leftPaddle), rightPaddle(rightPaddle), rng(system_clock::now().time_since_epoch().count()){
		//Set up box2d stuff
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = {startingPosition.x / SCALE, startingPosition.y / SCALE};
		shape.m_radius = 10.0f / SCALE;
		
		//set up the image
		image.setRadius(10.0f);
		image.setOrigin(image.getRadius() / 2.0f, image.getRadius() / 2.0f);
		image.setPosition(startingPosition);
		setSizeAndCenter(image, 10.0f);
	}

	~Ball(){
		game->DestroyBody(body);
	}

	void init() override{
		lightShape = std::make_shared<ltbl::LightShape>();
		lightShape->_shape.setPointCount(image.getPointCount());
		for(int i = 0; i < lightShape->_shape.getPointCount(); i++){
			lightShape->_shape.setPoint(i, image.getPoint(i));
		}
		lightShape->_shape.setPosition(image.getPosition());
		//create the body and set user data
		//setting the user data makes it so the beginCollision OF THIS COMPONENT is called
		//when this body collides with something
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		//create the fixture using the shape we set up before.
		//a body by itself does not have a shape. it needs a fixture
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);

		//set the initial velocity
		uniform_int_distribution<int> dist(0, 1);
		float direction = (float)dist(rng);
		float xVel;
		float yVel;
		if(direction == 0){
			xVel = -4;
		}else{
			xVel = 4;
		}
		uniform_int_distribution<int> yDist(-2, 2);
		yVel = (float)yDist(rng);
		body->SetLinearVelocity({xVel, yVel});

		owner->setZ(0);
	}

	void update(float frameTime) override{
		//see line 136 why we need to respawn the ball in the update function
		if(respawnBall){
			//to move the ball instantaniously, we have to destroy the body, then set the new position
			game->DestroyBody(body);
			bodyDef.position = {game->getSize().x / 2.0f / SCALE, (60 + (game->getSize().y / 2.0f)) / SCALE};
			//Then recreate the body and fixture
			init();
			respawnBall = false;
		}

		//update the position of the image every frame
		image.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		lightShape->_shape.setPosition(image.getPosition());
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(image);
	}

	void beginCollision(Component* component, b2Contact* contact) override{
		//check if this ball collided with a paddle
		if(auto paddle = dynamic_cast<Paddle*>(component)){
			//find the y coordinate where the ball collided
			float yIntersect = paddle->getPosition().y - image.getPosition().y;
			//divide that by the size of the paddle. this will give a number from -1 to 1
			float normalizedYIntersect = yIntersect / (paddle->getSize().y / 2.0f);
			//multiply by 60 (the max angle we are allowing the ball to bounce off the paddle)
			//and convert to radians
			//So if the ball hits the top of the paddle, it will bounce off at 60 degrees
			//if it hits the middle, it will bounce off completely horizontal
			float angle = normalizedYIntersect * 60.0f * DEGTORAD;
			b2Vec2 velocity;
			//calculate the velocity based on the angle
			velocity.y = speed * -sin(angle);
			if(paddle == leftPaddle){
				velocity.x = speed * cos(angle);
			}else if(paddle == rightPaddle){
				velocity.x = -speed * cos(angle);
			}
			//set the velocity
			body->SetLinearVelocity(velocity);
			//increase the speed every time the ball hits a paddle
			speed += .10f;
		}else if(auto boundary = dynamic_cast<Boundaries*>(component)){
			//if the ball hits a boundary and the ball is beyond the closest paddle, score a point
			if(image.getPosition().x > rightPaddle->getPosition().x - (rightPaddle->getSize().x / 2.0f)){
				printf("Left scores\n");
				score->score(left);
				//respawn the ball
				//we cant delete and reinitialize the ball inside the beginCollision function.
				//box2d will crash
				//set a flag and do it in the update function
				respawnBall = true;
			}else if(image.getPosition().x < leftPaddle->getPosition().x + (leftPaddle->getSize().x / 2.0f)){
				printf("Right scores\n");
				score->score(right);
				respawnBall = true;
			}
		}
	}
};
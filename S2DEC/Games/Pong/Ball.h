#pragma once
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "Component.h"
#include "Game.h"
#include "Paddle.h"
#include "Boundaries.h"
#include "Score.h"

using namespace S2D;

class Ball : public Component{
private:
	Game* game{nullptr};
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

public:
	//pass in the Score component and both Paddle components to do game logic later on
	Ball(Game* game, sf::Vector2f startingPosition, Score* score, Paddle* leftPaddle, Paddle* rightPaddle) : game(game), score(score), leftPaddle(leftPaddle), rightPaddle(rightPaddle){
		//Set up box2d stuff
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = {startingPosition.x / SCALE, startingPosition.y / SCALE};
		shape.m_radius = 10.0f / SCALE;
		
		//set up the image
		image.setRadius(10.0f);
		image.setOrigin(image.getRadius() / 2.0f, image.getRadius() / 2.0f);
		image.setPosition(startingPosition);
	}

	~Ball(){
		game->DestroyBody(body);
	}

	void init() override{
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
		body->SetLinearVelocity({4.0f, 1.0f});

		owner->setZ(0);
	}

	void update(float frameTime) override{
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
			if(image.getPosition().x > game->getSize().x / 2.0f){
				velocity.x = -speed * cos(angle);
				velocity.y = speed * -sin(angle);
				printf("Right paddle hit\n");
			}else{
				velocity.x = speed * cos(angle);
				velocity.y = speed * -sin(angle);
				printf("Left paddle hit\n");
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
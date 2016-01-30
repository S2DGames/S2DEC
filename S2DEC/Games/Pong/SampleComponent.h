#pragma once

#include "Game.h"

using namespace S2D;

class SampleComponent : public Component{
private:
	//stuff for box2d.
	b2Body* body{nullptr};
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{nullptr};
	b2Vec2 velocity{0.0f, 0.0f};

	sf::RectangleShape image;

	sf::Vector2f size;
public:
	SampleComponent(sf::Vector2f size) : size(size){
		
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override{
		//////////////////////////set up physics stuff////////////////////////////
		bodyDef.type = b2_dynamicBody;
		//start off in the center. note that we need to use this function to convert the window coordinates to physics world coordinates
		bodyDef.position = sfTob2(game->getView().getCenter());
		//Here we are using the same function on a single number as apposed to a vector
		shape.SetAsBox(sfTob2(size.x / 2.0f), sfTob2(size.y / 2.0f));
		//create the body
		body = game->CreateBody(&bodyDef);
		//we dont need this now but if this body were to collide with something, you need to set the user data so it is notified viea a callback function
		body->SetUserData(this);
		body->SetFixedRotation(true);
		//create the fixture.
		//a body does not have a shape unless it has a fixture
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);

		//////////////////////////set up image stuff///////////////////////////////
		image.setSize(size);
		movesfTob2(image, body);
	}

	/**
	* Called once every frame.
	*/
	void update(float frameTime) override{
		//check keyboard keys. There are 4 states,
		//KEY_PRESSED	- The key was just pressed
		//KEY_HELD		- The key was pressed and is still being pressed
		//KEY_RELEASED	- The key was just released
		//NOT_PRESSED	- The key is not pressed and has not just been released
		if(game->getKeyState(sf::Keyboard::Up) != NOT_PRESSED){
			velocity.y -= 1.0f;
		}
		if(game->getKeyState(sf::Keyboard::Down) != NOT_PRESSED){
			velocity.y += 1.0f;
		}
		if(game->getKeyState(sf::Keyboard::Left) != NOT_PRESSED){
			velocity.x -= 1.0f;
		}
		if(game->getKeyState(sf::Keyboard::Right) != NOT_PRESSED){
			velocity.x += 1.0f;
		}

		//set the velocity of the physics body
		body->SetLinearVelocity(velocity);

		//update the image position
		movesfTob2(image, body);
		//reser the velocity back to 0 so it only moves when a button is being pressed
		velocity = {0.0f, 0.0f};
	}

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override{
		//lastly draw the image
		target.draw(image);
	}
};
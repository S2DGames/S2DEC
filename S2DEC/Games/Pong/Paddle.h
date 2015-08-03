#pragma once
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Component.h"
#include "Game.h"
#include "sf_b2.h"

using namespace S2D;

using std::bind;

class Paddle : public Component{
private:
	//a simple rectangleshape to draw the paddle.
	sf::RectangleShape image;

	//box2d stuff
	//the body will be added to the physics world and we will pull the position from it every frame
	//to update the position of the image
	b2Body* body{nullptr};
	//the "body definition" is used to initialize the body.
	b2BodyDef bodyDef;
	//the shape is used to initialize the fixture.
	b2PolygonShape shape;
	//the fixture is added to the body to give it its shape.
	b2Fixture* fixture{nullptr};

	//2 keyboard keys that will control the paddle. we will set these in the constructor.
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;

	//the velocity that the body will be set to every frame.
	b2Vec2 velocity{0.0f, 0.0f};

public:

	//pass in the starting position, the size, and the controls for the paddle.
	Paddle(sf::Vector2f startingPosition, sf::Vector2f size, sf::Keyboard::Key up, sf::Keyboard::Key down) : up(up), down(down){
		//set up image stuff
		image.setSize(size);
		//set the center of the rectangle as the translation point or "origin"
		//SFML by default uses the top right but we want to use the center to
		//make it easier with Box2d later on.
		//You can do this easily by including sf_b2.h and calling 
		//setCenter(sf::RectangleShape& rs)
		//The basic SFML drawables are supported such as CircleShape, RectangleShape
		setCenter(image);
		image.setPosition(startingPosition);

		//set up box2d stuff
		bodyDef.type = b2_dynamicBody;
		//we need to convert the SFML position to the physics world position.
		//The easiest way to do this is to call sfTob2(sf::Vector2f vec) which is also in sf_b2.h
		bodyDef.position = sfTob2(startingPosition);
		shape.SetAsBox(sfTob2(size.x / 2.0f), sfTob2(size.y / 2.0f));
	}

	~Paddle(){
		//destroy the body to remove it from the box2d world.
		game->DestroyBody(body);
	}

	//these next 4 functions show how to use the event system. The check function returns a bool
	//and does not take any parameters. The move function has a void return and does not take any
	//parameters. The move function is called when the check function returns true.
	//adding the event to the event manager is at line 111.
	//Check the up key to see if it is pressed
	bool checkUp(){
		//easiest way to do this is to check if it is not pressed. However, this will also return
		//true for one extra frame when the key is released
		return game->getKeyState(up) != NOT_PRESSED;
	}

	//check the down key
	bool checkDown(){
		return game->getKeyState(down) != NOT_PRESSED;
	}

	//set the velocity when the up key is pressed
	void moveUp(){
		velocity.y -= 10.0f;
	}

	//set the velolcity when the down key is pressed
	void moveDown(){
		velocity.y += 10.0f;
	}

	void init() override{
		//create the body and set user data
		//User data is used to determine what components collided.
		//If you don't set this, you will not be able to tell what components collided and the
		//beginCollision and endCollision callback functions will not fire for the component.
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);

		//create the fixture.
		//a body does not have a shape unless it has a fixture
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);

		//set the z layer of this object
		//the z layer determines when entity gets drawn each frame. (this is just a placeholder for now. later all components will have their own z)
		owner->setZ(1);

		//set up the callback events for keyboard input. note: bind is an std function
		//so either add 'using std::bind' to the top of your header files or always use std::bind
		game->watchEvent(bind(&Paddle::checkUp, this), bind(&Paddle::moveUp, this), this);
		game->watchEvent(bind(&Paddle::checkDown, this), bind(&Paddle::moveDown, this), this);
	}

	void update(float frameTime) override{
		//movesfTob2 is a utility function that sets the position of an sf::Transformable
		//to the position of a box2d body.
		movesfTob2(image, body);

		//set the velocity of the physics body.
		body->SetLinearVelocity(velocity);
		//reset the velocity so the paddle will stop if no key is pressed.
		velocity.y = 0.0f;
	}

	void draw(sf::RenderTarget& target) override{
		//drawing is pretty simple
		//The target is the canvas that will be drawn to.
		target.draw(image);
	}

	const sf::Vector2f& getPosition(){
		return image.getPosition();
	}

	const sf::Vector2f& getSize(){
		return image.getSize();
	}
};
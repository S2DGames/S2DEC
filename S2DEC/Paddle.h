#pragma once
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Component.h"
#include "Game.h"

using namespace S2D;

class Paddle : public Component{
private:
	Game* game{nullptr};
	b2Body* body{nullptr};
	b2BodyDef bodyDef{};
	b2PolygonShape shape{};
	b2Fixture* fixture{nullptr};

	sf::RectangleShape image;

	sf::Keyboard::Key up;
	sf::Keyboard::Key down;

public:

	//pass in the starting position for the paddle and the controls
	Paddle(Game* game, sf::Vector2f startingPosition, sf::Keyboard::Key up, sf::Keyboard::Key down) : game(game), up(up), down(down){
		//set up box2d stuff
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = {startingPosition.x / SCALE, startingPosition.y / SCALE};
		shape.SetAsBox(25.0f / SCALE / 2.0f, 150.0f / SCALE / 2.0f);
		
		//set up image stuff
		image.setSize({25.0f, 150.0f});
		image.setOrigin(image.getSize().x / 2.0f, image.getSize().y / 2.0f);
		image.setPosition(startingPosition);
	}

	~Paddle(){
		game->DestroyBody(body);
	}

	void init() override{
		//create the body and set user data
		//setting the user data makes it so the beginCollision OF THIS COMPONENT is called
		//when this body collides with something
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);

		//create the fixture.
		//a body does not have a shape unless it has a fixture
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);

		//set the z layer of this object
		owner->setZ(1);
	}

	void update(float frameTime) override{
		image.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});

		b2Vec2 velocity{0.0f, 0.0f};

		if(game->getKeyState(up)){
			velocity.y -= 10.0f;
		}

		if(game->getKeyState(down)){
			velocity.y += 10.0f;
		}

		body->SetLinearVelocity(velocity);
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(image);
#ifdef _DEBUG
#ifndef IGNORE_DEBUG
		sf::RectangleShape outline;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(1.0f);
		outline.setSize({25.0f, 150.0f});
		outline.setOrigin(outline.getSize().x / 2.0f, outline.getSize().y / 2.0f);
		outline.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		target.draw(outline);
#endif
#endif
	}

	const sf::Vector2f& getPosition(){
		return image.getPosition();
	}

	const sf::Vector2f& getSize(){
		return image.getSize();
	}

};
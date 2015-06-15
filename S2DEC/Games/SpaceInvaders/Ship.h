#pragma once

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Body.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Component.h"
#include "Game.h"
#include "Util.h"

using namespace S2D;

class Ship : public Component{
private:
	Game* game{nullptr};
	b2Body* body{nullptr};
	b2BodyDef bodyDef{};
	b2PolygonShape shape{};
	b2Fixture* fixture{nullptr};

	sf::RectangleShape image;
public:
	Ship(Game* game) : game(game){
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = {(game->getSize().x / 2.0f) / SCALE, (game->getSize().y - 20.0f) / SCALE};
		shape.SetAsBox(10.0f / SCALE, 10.0f / SCALE);
		image.setSize({20.0f, 20.0f});
		image.setOrigin(image.getSize().x / 2.0f, image.getSize().y / 2.0f);
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override{
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
	}

	/**
	* Called when the Game starts.
	*/
	void onStart() override{

	}

	/**
	* Called once every frame.
	*/
	void update(float frameTime) override{
		b2Vec2 velocity{0.0f, 0.0f};

		if(game->getKeyState(sf::Keyboard::Key::A)){
			velocity.x -= 4.0f;
		}

		if(game->getKeyState(sf::Keyboard::Key::D)){
			velocity.x += 4.0f;
		}

		body->SetLinearVelocity(velocity);

		image.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	}

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override{
		target.draw(image);
		//Uncomment this, include "SFML/Graphics/RectangleShape.hpp", and set the size of the RectangleShape
		//if you want the physics body to be outlined.
		/*#ifdef _DEBUG
		#ifndef IGNORE_DEBUG
		sf::RectangleShape outline;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(1.0f);
		outline.setSize({10.0f, 10.0f});
		outline.setOrigin(outline.getSize().x / 2.0f, outline.getSize().y / 2.0f);
		outline.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		target.draw(outline);
		#endif
		#endif*/
	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	* Do not delete or add physics objects in the scope of this function.
	*/
	void beginCollision(Component* collidedComponent, b2Contact* contact) override{

	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	* Do not delete or add physics objects in the scope of this function.
	*/
	void endCollision(Component* collidedComponent, b2Contact* contact) override{

	}

	b2Vec2 getb2Position(){
		return body->GetPosition();
	}
};